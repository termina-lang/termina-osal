
#include <termina.h>

#include <termina/shared/periodic_timer.h>

__termina_shared_periodic_timer_t __termina_shared_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

void __termina_periodic_timer__init(const __termina_id_t timer_id,
                                    const __termina_periodic_timer_connection_t * const connection,
                                    const TimeVal * const period,
                                    Status * const status) {

    status->__variant = Status__Success;

    if (__TERMINA_APP_CONFIG_PERIODIC_TIMERS <= timer_id) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    if (status->__variant == Status__Success) {

        __termina_shared_periodic_timer_t * timer = __termina_shared_timer__get_timer(timer_id);

        timer->timer_id = timer_id;
        timer->connection = *connection;
        timer->period = *period;

        __termina_periodic_timer_os__init(timer_id, status);

    }

    return;

}
