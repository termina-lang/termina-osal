
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Keyboard of the POSIX emulation, whose input is delivered as an
 *        interrupt.
 */

#include "config.h"

#include <termina.h>

#include <termina/shared/except.h>
#include <termina/shared/interrupt.h>
#include <termina/shared/msg_queue.h>
#include <termina/os/posix/keyboard.h>
#include <termina/os/posix/task.h>

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

static pthread_t kbd_task;

static void (*termina__posix__keyboard__irq_target)(void) = NULL;

void termina__posix__keyboard__irq_handler(int signum) {

    (void)signum;

    if (NULL != termina__posix__keyboard__irq_target) {

        // Increments the blocking nesting level, since the handler runs with
        // the signals blocked.
        termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level + 1;

        // Disables the scheduling, so that no context switch happens while
        // the handler runs.
        termina__posix__task__disable_scheduling = 1;

        // Serves the keyboard interrupt.
        termina__posix__keyboard__irq_target();

        termina__posix__task__disable_scheduling = 0;

        termina__posix__task__schedule();

        // Decrements the blocking nesting level on leaving the handler.
        termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level - 1;

    }

    return;

}

static void termina__posix__keyboard__irq_task_connection_handler(void) {

    // Sends the interrupt identifier to the connected task.

    uint32_t interrupt_id = 0;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_object_table[0];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = interrupt->connection.task.task_id,
        .port_id = interrupt->connection.task.sink_port_id
    };

    termina__shared__msg_queue__deliver(interrupt->connection.task.sink_msgq_id,
                                        &interrupt_id,
                                        interrupt->connection.task.task_msg_queue_id,
                                        &event, 0U);

}

static void termina__posix__keyboard__irq_handler_connection_handler(void) {

    // Executes the action of the connected handler.

    uint32_t interrupt_id = 0;

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_object_table[0];

    termina__event_t event = {
        .emitter_id = interrupt->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = interrupt->connection.handler.handler_id,
        .port_id = 0 // A handler has a single sink port, whose identifier is 0.
    };

    interrupt->connection.handler.handler_action(&event,
                interrupt->connection.handler.handler_object, interrupt_id);

}

// Number of bytes waiting in the standard input, or zero when the system cannot
// tell.
static int termina__posix__keyboard__pending(void) {

    int pending = 0;

    if (0 != ioctl(STDIN_FILENO, FIONREAD, &pending)) {
        pending = 0;
    }

    return pending;

}

static void * termina__posix__keyboard__poll_task(void * arg) {

    (void)arg;

    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;

    for (;;) {

        int ret = poll(&pfd, 1, -1);

        if ((ret < 0) && (EINTR == errno)) {

            // A signal interrupted the wait, which is not an error: wait again

        } else if ((ret > 0) && (0 != (pfd.revents & POLLHUP))
                   && (0 == termina__posix__keyboard__pending())) {

            // The standard input has been closed and nothing is left to read,
            // so no key will come. Some systems report it as readable as well.
            (void)fprintf(stderr, "termina: the standard input has been closed; "
                                  "the keyboard interrupt will not fire again\n");
            break;

        } else if ((ret > 0) && (0 != (pfd.revents & POLLIN))) {

            // Sends SIGUSR2 to the thread of the current task.
            termina__posix__task_t * current_task = termina__posix__task__get_task(termina__posix__current_task_id);

            pthread_kill(current_task->pthread, SIGUSR2);
            usleep(TERMINA__TIME__MICROSECONDS_PER_TICK);

        } else {

            // A failure of poll() ends the polling.
            break;

        }

    }

    return NULL;

}

void termina__posix__keyboard__irq_init(termina__error_code_t * const status) {

    termina__shared__interrupt_t * interrupt = &termina__shared__interrupt_object_table[0];

    *status = termina__error__none;

    if (termina__emitter_connection_type__task == interrupt->connection.type) {
        termina__posix__keyboard__irq_target = termina__posix__keyboard__irq_task_connection_handler;
    } else {
        termina__posix__keyboard__irq_target = termina__posix__keyboard__irq_handler_connection_handler;
    }

    // Creates the thread that polls the standard input.

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&kbd_task, &attr, termina__posix__keyboard__poll_task, NULL);

}

void termina__posix__keyboard__init(void) {

    // Configures the standard input as non-blocking.
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    return;

}