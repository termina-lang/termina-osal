
#include <termina.h>

#include <termina/shared/list/list.h>
#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/posix/time.h>
#include <termina/os/posix/periodic_timer.h>


__posix_periodic_timer_t __posix_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

__termina_shared_list_t __posix_timers_list;

static void __posix_timer__task_connection_handler(
    const __termina_shared_periodic_timer_t * const timer,
    const TimeVal *const current_time) {

    int32_t status = 0;

    __termina_event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = __termina_active_entity__task,
        .owner.task.task_id = timer->connection.task.task_id,
        .port_id = timer->connection.task.sink_port_id
    };

    // Send a message to the task
    __termina_msg_queue__send(timer->connection.task.sink_msgq_id,
                              current_time, &status);

    if (0 == status) {

        __termina_msg_queue__send(timer->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

static void __posix_timer__handler_connection_handler(
    const __termina_shared_periodic_timer_t * const timer,
    const TimeVal * const current_time) {

    __status_int32_t status;

    __termina_event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = __termina_active_entity__handler,
        .owner.handler.handler_id = timer->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    status = timer->connection.handler.handler_action(&event,
                                                      timer->connection.handler.handler_object,
                                                      *current_time);

    if (Success != status.__variant) {

        ExceptSource source;
        source.__variant = ExceptSource__Handler;
        source.Handler.__0 = timer->connection.handler.handler_id;

        // Trigger the exception
        // Since the handler only has one sink port, we do not need to
        // store the sink port id. The sink port id is always 0.
        __termina_except__action_failure(source, 0, status.Failure.__0);
    }

}

void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
                                       int32_t * const status) {

    TimeVal current_time = {0, 0};
    __termina_shared_periodic_timer_t * timer = __termina_shared_timer__get_timer(timer_id);
    __posix_periodic_timer_t * posix_timer = __posix_timer__get_timer(timer_id);

    *status = 0;

    // Install handler depending on the connection type
    if (timer->connection.type == __termina_emitter_connection_type__handler) {
        posix_timer->handler = __posix_timer__handler_connection_handler;
    } else {
        posix_timer->handler = __posix_timer__task_connection_handler;
    }

    // Get current time in timeval format
    __posix_time__get_current_time(&current_time);

    // Load the timer
    TimeVal next_abs_time = current_time;
    __termina_shared__add_timeval(&next_abs_time, &timer->period);
    __termina_shared_list__time_add(&__posix_timers_list, timer_id, &next_abs_time, status);

    return;

}
