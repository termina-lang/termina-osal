#ifndef __TERMINA__OS__POSIX__PERIODIC_TIMER_H__
#define __TERMINA__OS__POSIX__PERIODIC_TIMER_H__

#include <termina.h>

typedef void (*__posix_periodic_timer_handler_t)(
    const __termina_shared_periodic_timer_t * const timer,
    const TimeVal * const current_time);

typedef struct {

    __posix_periodic_timer_handler_t handler;

} __posix_periodic_timer_t;

extern __posix_periodic_timer_t __posix_timers[__TERMINA_APP_CONFIG_PERIODIC_TIMERS];

static inline __posix_periodic_timer_t * __posix_timer__get_timer(const __termina_id_t timer_id) {
    return &__posix_timers[timer_id];
}


#endif // __TERMINA__OS__POSIX__PERIODIC_TIMER_H__