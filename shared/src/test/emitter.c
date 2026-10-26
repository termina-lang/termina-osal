#include <termina.h>
#include <termina/shared/msg_queue.h>

/**
 * \brief Priority of the task of the case while a handler runs.
 */
#define TERMINA__TEST__EMITTER__HANDLER_PRIORITY 1U

void termina__test__emitter__fire(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const void * const value) {

    const termina__test__emitter_t * self = (const termina__test__emitter_t * const)termina__this;

    (void)termina__ev; // The emitter takes no lock

    if (termina__emitter_connection_type__task == self->type) {

        const termina__event_t event = {
            .emitter_id = self->emitter_id,
            .owner.type = termina__active_entity__task,
            .owner.task.task_id = self->task.task_id,
            .port_id = self->task.sink_port_id
        };

        termina__shared__msg_queue__deliver(self->task.sink_msgq_id,
                                            value,
                                            self->task.task_msg_queue_id,
                                            &event);

    } else {

        termina__error_code_t status = termina__error__none;

        const termina__event_t event = {
            .emitter_id = self->emitter_id,
            .owner.type = termina__active_entity__handler,
            .owner.handler.handler_id = self->handler.handler_id,
            .port_id = 0U // A handler has a single sink port
        };

        // No task preempts the handler, as on the exit of an interrupt
        termina__task__set_current_priority(TERMINA__TEST__EMITTER__HANDLER_PRIORITY, &status);

        if (termina__error__none != status) {

            termina__except__runtime_failure(termina__runtime_operation__task_priority, status);

        }

        self->handler.handler_action(&event, value);

        termina__task__reset_priority(&status);

        if (termina__error__none != status) {

            termina__except__runtime_failure(termina__runtime_operation__task_priority, status);

        }

    }

}
