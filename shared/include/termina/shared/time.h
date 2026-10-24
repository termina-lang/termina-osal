#ifndef TERMINA__SHARED__TIME_H__
#define TERMINA__SHARED__TIME_H__

#include "config.h"

#include <termina.h>


/**
 * \brief Increments one timeval by another.
 *
 * @param[inout] rhs    the timeval to be incremented.
 * @param[in] rhs       the increment.
 */
void termina__shared__add_timeval(TimeVal * const lhs, const TimeVal * const rhs);

/**
 * \brief Returns the number of ticks per second.
 */
static inline uint64_t termina__shared__time__ticks_per_sec(void) {
    return 1000000U / TERMINA__TIME__MICROSECONDS_PER_TICK;
}

/**
 * \brief Returns the time elapsed since boot.
 *
 * This function shall be implemented for each operating system.
 *
 * @param[out] uptime      the amount of elapsed time since boot.
 */
void termina__os__time__clock_get_uptime(TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * This function shall be implemented for each operating system.
 *
 * @param[in] time_val    the amount of time that the task will be blocked.
 */
void termina__os__time__delay_in(const TimeVal * const time_val);

#endif // TERMINA__SHARED__TIME_H__