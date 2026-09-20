
#include <termina.h>

#include <termina/shared/list/list.h>
#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/posix/time.h>
#include <termina/os/posix/periodic_timer.h>


__posix_periodic_timer_t __posix_timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

termina__shared_list_t __posix_timers_list;

static void __posix_timer__task_connection_handler(
    const termina__shared_periodic_timer_t * const timer,
    const TimeVal *const current_time) {

    int32_t status = 0;

    termina__event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = termina__active_entity__task,
        .owner.task.task_id = timer->connection.task.task_id,
        .port_id = timer->connection.task.sink_port_id
    };

    // Send a message to the task
    termina__msg_queue__send(timer->connection.task.sink_msgq_id,
                              current_time, &status);

    if (0 == status) {

        termina__msg_queue__send(timer->connection.task.task_msg_queue_id,
                                  &event, &status);

    }

}

static void __posix_timer__handler_connection_handler(
    const termina__shared_periodic_timer_t * const timer,
    const TimeVal * const current_time) {

    Status__i32 status;

    termina__event_t event = {
        .emitter_id = timer->emitter_id,
        .owner.type = termina__active_entity__handler,
        .owner.handler.handler_id = timer->connection.handler.handler_id,
        .port_id = 0 // The handler only has one sink port, so we set it to 0
    };

    status = timer->connection.handler.handler_action(&event,
                                                      timer->connection.handler.handler_object,
                                                      *current_time);

    if (Status__Success != status._variant) {

        ExceptSource source;
        source._variant = ExceptSource__Handler;
        source.Handler._0 = timer->connection.handler.handler_id;

        // Trigger the exception
        // Since the handler only has one sink port, we do not need to
        // store the sink port id. The sink port id is always 0.
        termina__except__action_failure(source, 0, status.Failure._0);
    }

}

void termina__periodic_timer_os__init(const termina__id_t timer_id,
                                       int32_t * const status) {

    TimeVal current_time = {0, 0};
    termina__shared_periodic_timer_t * timer = termina__shared_timer__get_timer(timer_id);
    __posix_periodic_timer_t * posix_timer = __posix_timer__get_timer(timer_id);

    *status = 0;

    // Install handler depending on the connection type
    if (timer->connection.type == termina__emitter_connection_type__handler) {
        posix_timer->handler = __posix_timer__handler_connection_handler;
    } else {
        posix_timer->handler = __posix_timer__task_connection_handler;
    }

    // Get current time in timeval format
    __posix_time__get_current_time(&current_time);

    // Load the timer
    TimeVal next_abs_time = current_time;
    termina__shared__add_timeval(&next_abs_time, &timer->period);
    termina__shared_list__time_add(&__posix_timers_list, timer_id, &next_abs_time, status);

    return;

}
