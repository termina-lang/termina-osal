#ifndef TERMINA__OS__POSIX__PERIODIC_TIMER_H__
#define TERMINA__OS__POSIX__PERIODIC_TIMER_H__

#include <termina.h>
#include <termina/shared/periodic_timer.h>

typedef void (*__posix_periodic_timer_handler_t)(
    const termina__shared_periodic_timer_t * const timer,
    const TimeVal * const current_time);

typedef struct {

    __posix_periodic_timer_handler_t handler;

} __posix_periodic_timer_t;

extern __posix_periodic_timer_t __posix_timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

static inline __posix_periodic_timer_t * __posix_timer__get_timer(const termina__id_t timer_id) {
    return &__posix_timers[timer_id];
}


#endif // TERMINA__OS__POSIX__PERIODIC_TIMER_H__