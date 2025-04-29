
#include <termina.h>

#include <termina/shared/list/list.h>
#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>

#include <termina/os/posix/time.h>
#include <termina/os/posix/periodic_timer.h>


__posix_periodic_timer_t __posix_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

__termina_shared_list_t __posix_timers_list;

static void __posix_timer__task_connection_handler(
    const __termina_periodic_timer_connection_t *const port_connection,
    const TimeVal *const current_time) {

    Status status;
    status.__variant = Status__Success;

    // Send a message to the task
    __termina_msg_queue__send(port_connection->task.sink_msgq_id,
                              current_time, &status);

    if (Status__Success == status.__variant) {

        __termina_msg_queue__send(port_connection->task.task_msg_queue_id,
                                &port_connection->task.sink_port_id, &status);

    }

}

static void __posix_timer__handler_connection_handler(
    const __termina_periodic_timer_connection_t *const port_connection,
    const TimeVal *const current_time) {

    __action_result_t result;

    result = port_connection->handler.handler_action(port_connection->handler.handler_object,
                                                     *current_time);

    if (__action_result__return != result.__variant) {
        __termina_exec__shutdown();
    }

}

void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
                                       Status *const status) {

    TimeVal current_time = {0, 0};
    __termina_shared_periodic_timer_t *timer = __termina_shared_timer__get_timer(timer_id);
    __posix_periodic_timer_t *posix_timer = __posix_timer__get_timer(timer_id);

    status->__variant = Status__Success;

    // Install handler depending on the connection type
    if (timer->connection.type == __TerminaEmitterConnectionType__Handler)
    {
        posix_timer->handler = __posix_timer__handler_connection_handler;
    }
    else
    {
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
