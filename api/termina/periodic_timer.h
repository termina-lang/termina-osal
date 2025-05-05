#ifndef __TERMINA__PERIODIC_TIMER_H__
#define __TERMINA__PERIODIC_TIMER_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * \brief Creates a timer.
 * 
 * @param[in]   timer_id    the identifier of the timer.
 * @param[in]   connection  the connection of the timer.
 * @param[in]   period      the period of the timer.
 * @param[out]  status      the status of the operation.
 */
void __termina_periodic_timer__init(const __termina_id_t timer_id,
                                    const __termina_periodic_timer_connection_t * const connection,
                                    const TimeVal * const period,
                                    int32_t * const status);


#endif // __TERMINA__PERIODIC_TIMER_H__
