
#include "config.h"

#include <termina.h>

#include <termina/shared/interrupt.h>
#include <termina/os/posix/task.h>

#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

static pthread_t kbd_task;

static void (*__posix_keyboard__irq_target)(void) = NULL;

void __posix_keyboard__irq_handler(int signum) {

    if (NULL != __posix_keyboard__irq_target) {

        // Increment the blocking nesting level to indicate that the tick handler is
        // running with the signals disabled
        __posix_blocking_nesting_level = __posix_blocking_nesting_level + 1;

        // Disable the scheduling to avoid context switches when executing
        // the handler
        __posix_task__disable_scheduling = 1;

        // Trigger the tick computation
        __posix_keyboard__irq_target();

        __posix_task__disable_scheduling = 0;

        __posix_task__schedule();

        // Decrement the blocking nesting level to indicate that we are leaving the
        // critical section of the tick handler
        __posix_blocking_nesting_level = __posix_blocking_nesting_level - 1;

    }

    return;

}

static void __posix_keyboard__irq_task_connection_handler() {

    // We need to send the message to the connected task

    uint32_t interrupt_id = 0;
    int32_t status = 0;

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[0];

    __termina_event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = __termina_active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id 
    };

    __termina_msg_queue__send(interrupt->connection.task.sink_msgq_id,
                              &interrupt_id, &status);

    if (0 == status) {

        // Notify the task that a message has been sent
        __termina_msg_queue__send(interrupt->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

void __posix_keyboard__irq_handler_connection_handler() {

    // It is a handler. We need to execute it

    uint32_t interrupt_id = 0;
    __status_int32_t result;
    result.__variant = Success;

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[0];

    __termina_event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = __termina_active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    result = interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);
    
    if (Success != result.__variant) {
        __termina_exec__reboot();
    }

}

static void * __posix_keyboard__poll_task(void * arg) {

    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;

    for (;;) {

        int ret = poll(&pfd, 1, -1);

        if (ret > 0 && (pfd.revents & POLLIN)) {

            // Get the POSIX internal structure of the current task
            __posix_task_t * current_task = __posix_task__get_task(__posix_current_task_id);

            pthread_kill(current_task->pthread, SIGUSR2);

        } else {
            // TODO: An error ocurred. We just ignore it for the time being
            break;
        }

    }

    return NULL;

}

void __posix_keyboard__irq_init(int32_t * const status) {

    __termina_shared_interrupt_t * interrupt = &__shared_interrupt_table[0];

    *status = 0;

    if (__termina_emitter_connection_type__task == interrupt->connection.type) {
        __posix_keyboard__irq_target = __posix_keyboard__irq_task_connection_handler;
    } else {
        __posix_keyboard__irq_target = __posix_keyboard__irq_handler_connection_handler;
    }

    // Create the task that shall poll on STDIN

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&kbd_task, &attr, __posix_keyboard__poll_task, NULL);

}

void __posix_keyboard__init(void) {

    // Configure the STDIN to be non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    return;

}