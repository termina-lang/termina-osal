#ifndef TERMINA__PERIODIC_TIMER_H__
#define TERMINA__PERIODIC_TIMER_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * \brief Creates a timer.
 * 
 * @param[in]   timer_id    the identifier of the timer.
 * @param[in]   emitter_id  the identifier of the emitter.
 * @param[in]   connection  the connection of the timer.
 * @param[in]   period      the period of the timer.
 * @param[out]  status      the status of the operation.
 */
void termina__periodic_timer__init(const termina__id_t timer_id,
                                    const termina__id_t emitter_id,
                                    const termina__periodic_timer_connection_t * const connection,
                                    const TimeVal * const period,
                                    termina__error_code_t * const status);


#endif // TERMINA__PERIODIC_TIMER_H__
