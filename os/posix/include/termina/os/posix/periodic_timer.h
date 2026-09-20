#ifndef TERMINA__OS__POSIX__PERIODIC_TIMER_H__
#define TERMINA__OS__POSIX__PERIODIC_TIMER_H__

#include <termina.h>
#include <termina/shared/periodic_timer.h>

typedef void (*termina__posix__periodic_timer_handler_t)(
    const termina__shared__periodic_timer_t * const timer,
    const TimeVal * const current_time);

typedef struct {

    termina__posix__periodic_timer_handler_t handler;

} termina__posix__periodic_timer_t;

extern termina__posix__periodic_timer_t termina__posix__timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

static inline termina__posix__periodic_timer_t * termina__posix__timer__get_timer(const termina__id_t timer_id) {
    return &termina__posix__timers[timer_id];
}


#endif // TERMINA__OS__POSIX__PERIODIC_TIMER_H__