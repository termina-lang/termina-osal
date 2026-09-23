
#include <termina.h>

#include <termina/shared/periodic_timer.h>

termina__shared__periodic_timer_t termina__shared__periodic_timer_object_table[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

void termina__periodic_timer__init(const termina__id_t timer_id,
                                    const termina__id_t emitter_id,
                                    const termina__periodic_timer_connection_t * const connection,
                                    const TimeVal * const period,
                                    int32_t * const status) {

    *status = 0;

    if (!termina__shared__timer__is_valid_id(timer_id)) {

        *status = -1;

    }

    if (0 == *status) {

        termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(timer_id);

        timer->emitter_id = emitter_id;
        timer->timer_id = timer_id;
        timer->connection = *connection;
        timer->period = *period;

        termina__periodic_timer_os__init(timer_id, status);

    }

    return;

}
