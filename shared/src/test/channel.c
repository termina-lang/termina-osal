#include <termina.h>
#include <termina/shared/msg_queue.h>

void termina__test__channel__pending(const termina__event_t * const termina__ev,
                                     const void * const termina__this,
                                     size_t * const n) {

    const termina__msg_queue_t * self = (const termina__msg_queue_t * const)termina__this;

    termina__error_code_t status = termina__error__none;

    (void)termina__ev; // The channel takes no lock

    termina__msg_queue__get_pending(self->channel_msg_queue_id, n, &status);

    if (termina__error__none != status) {

        termina__except__msg_queue_recv_error(self->channel_msg_queue_id, status);

    }

}

void termina__test__channel__take(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  termina__enum__Option_t * const variant,
                                  void * const element) {

    const termina__msg_queue_t * self = (const termina__msg_queue_t * const)termina__this;

    termina__error_code_t status = termina__error__none;

    _Bool received = false;

    (void)termina__ev; // The channel takes no lock

    *variant = Option__None;

    termina__msg_queue__try_recv(self->channel_msg_queue_id, element, &received, &status);

    if (termina__error__none != status) {

        termina__except__msg_queue_recv_error(self->channel_msg_queue_id, status);

    }

    if (received) {

        termina__event_t event;

        _Bool event_received = false;

        // Discards the event that stands for the one of a receiving task
        termina__msg_queue__try_recv(self->task_msg_queue_id, &event, &event_received, &status);

        if (termina__error__none != status) {

            termina__except__msg_queue_recv_error(self->task_msg_queue_id, status);

        }

        if (!event_received) {

            // A message without its event: the two queues are out of step
            termina__except__msg_queue_recv_error(self->task_msg_queue_id,
                                                  termina__error__receive_failed);

        }

        *variant = Option__Some;

    }

}

void termina__test__channel__flush(const termina__msg_queue_t * const channel) {

    termina__error_code_t status = termina__error__none;

    termina__shared__msg_queue__flush(channel->channel_msg_queue_id, &status);

    if (termina__error__none == status) {

        termina__shared__msg_queue__flush(channel->task_msg_queue_id, &status);

    }

    if (termina__error__none != status) {

        termina__except__runtime_failure(0U, termina__runtime_operation__test_reset, status);

    }

}
