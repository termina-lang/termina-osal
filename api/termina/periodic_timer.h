/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the periodic timers.
 */

#ifndef TERMINA__PERIODIC_TIMER_H__
#define TERMINA__PERIODIC_TIMER_H__

#include <termina/types.h>
#include <termina/emitter.h>
#include <termina/prelude.h>

/**
 * @brief Creates a periodic timer.
 * 
 * @param[in]   timer_id    Identifier of the timer.
 * @param[in]   emitter_id  Identifier of the emitter.
 * @param[in]   connection  Connection of the timer.
 * @param[in]   period      Period of the timer.
 * @param[out]  status      Status of the operation: `termina__error__none`, or
 *                          `termina__error__timer_init` if the timer cannot be
 *                          created.
 */
void termina__periodic_timer__init(const termina__id_t timer_id,
                                    const termina__id_t emitter_id,
                                    const termina__periodic_timer_connection_t * const connection,
                                    const TimeVal * const period,
                                    termina__error_code_t * const status);


#endif // TERMINA__PERIODIC_TIMER_H__
