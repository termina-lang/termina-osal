/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Periodic timers of the POSIX emulation.
 */

#ifndef TERMINA__OS__POSIX__PERIODIC_TIMER_H__
#define TERMINA__OS__POSIX__PERIODIC_TIMER_H__

#include <termina.h>
#include <termina/shared/periodic_timer.h>

/**
 * @brief Function that serves the expiry of a periodic timer.
 */
typedef void (*termina__posix__periodic_timer_handler_t)(
    const termina__shared__periodic_timer_t * const timer,
    const TimeVal * const scheduled_time);

/**
 * @brief Periodic timer of the POSIX emulation.
 */
typedef struct {

    //! Function that serves the expiry of the timer.
    termina__posix__periodic_timer_handler_t handler;

    //! Time at which the timer is next due.
    TimeVal next_time;

} termina__posix__periodic_timer_t;

/** @brief Table of the periodic timers of the POSIX emulation. */
extern termina__posix__periodic_timer_t termina__posix__timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

/**
 * @brief Gets the POSIX timer object of an identifier, which must be valid.
 *
 * @param[in] timer_id  Identifier of the timer.
 *
 * @return Pointer to the timer object.
 */
static inline termina__posix__periodic_timer_t * termina__posix__timer__get_timer(const termina__id_t timer_id) {
    return &termina__posix__timers[timer_id];
}


#endif // TERMINA__OS__POSIX__PERIODIC_TIMER_H__