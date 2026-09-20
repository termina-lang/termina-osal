
#include "config.h"

#include <termina.h>

#include <termina/shared/interrupt.h>
#include <termina/os/posix/keyboard.h>
#include <termina/os/posix/task.h>

#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

static pthread_t kbd_task;

static void (*termina__posix__keyboard__irq_target)(void) = NULL;

void termina__posix__keyboard__irq_handler(int signum) {

    (void)signum;

    if (NULL != termina__posix__keyboard__irq_target) {

        // Increment the blocking nesting level to indicate that the irq handler is
        // running with the signals disabled
        termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level + 1;

        // Disable the scheduling to avoid context switches when executing
        // the handler
        termina__posix__task__disable_scheduling = 1;

        // Trigger the tick computation
        termina__posix__keyboard__irq_target();

        termina__posix__task__disable_scheduling = 0;

        termina__posix__task__schedule();

        // Decrement the blocking nesting level to indicate that we are leaving the
        // critical section of the irq handler
        termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level - 1;

    }

    return;

}

static void termina__posix__keyboard__irq_task_connection_handler(void) {

    // We need to send the message to the connected task

    uint32_t interrupt_id = 0;
    int32_t status = 0;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[0];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id 
    };

    termina__msg_queue__send(interrupt->connection.task.sink_msgq_id,
                              &interrupt_id, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        termina__msg_queue__send(interrupt->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

static void termina__posix__keyboard__irq_handler_connection_handler(void) {

    // It is a handler. We need to execute it

    uint32_t interrupt_id = 0;
    Status__i32 result;
    result._variant = Status__Success;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[0];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    result = interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);
    
    if (Status__Success != result._variant) {
        termina__exec__reboot();
    }

}

static void * termina__posix__keyboard__poll_task(void * arg) {

    (void)arg;

    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;

    for (;;) {

        int ret = poll(&pfd, 1, -1);

        if (ret > 0 && (pfd.revents & POLLIN)) {

            // Get the POSIX internal structure of the current task
            termina__posix__task_t * current_task = termina__posix__task__get_task(termina__posix__current_task_id);

            pthread_kill(current_task->pthread, SIGUSR2);
            usleep(TERMINA__TIME__MICROSECONDS_PER_TICK);

        } else {
            // TODO: An error ocurred. We just ignore it for the time being
            break;
        }

    }

    return NULL;

}

void termina__posix__keyboard__irq_init(int32_t * const status) {

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_table[0];

    *status = 0;

    if (termina__emitter_connection_type__task == interrupt->connection.type) {
        termina__posix__keyboard__irq_target = termina__posix__keyboard__irq_task_connection_handler;
    } else {
        termina__posix__keyboard__irq_target = termina__posix__keyboard__irq_handler_connection_handler;
    }

    // Create the task that shall poll on STDIN

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&kbd_task, &attr, termina__posix__keyboard__poll_task, NULL);

}

void termina__posix__keyboard__init(void) {

    // Configure the STDIN to be non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    return;

}