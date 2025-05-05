#ifndef __TERMINA__SHARED__PERIODIC_TIMER_H__
#define __TERMINA__SHARED__PERIODIC_TIMER_H__

#include <termina.h>

typedef struct {

    // \brief Identifier of the timer
    __termina_id_t timer_id;

    //! Source port of the timer event 
    __termina_periodic_timer_connection_t connection;

    //! Period of the timer
    TimeVal period;

} __termina_shared_periodic_timer_t;

/**
 * \brief Array of timer objects.
 */
extern __termina_shared_periodic_timer_t __termina_shared_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

static inline __termina_shared_periodic_timer_t * __termina_shared_timer__get_timer(const __termina_id_t timer_id) {
    return &__termina_shared_timers[timer_id];
}

/**
 * \brief Creates a periodic timer.
 *        Operating system implementation-dependent function.
 * 
 * @param[in]   timer_id  the identifier of the timer.
 * @param[out]  status    Zero if the timer was created correctly or
 *                        a different value in case of error.
 */
void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
                                       int32_t * const status);


#endif // __TERMINA__SHARED__PERIODIC_TIMER_H__
