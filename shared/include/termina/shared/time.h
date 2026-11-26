/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Time operations, partly implemented by each operating system.
 */

#ifndef TERMINA__SHARED__TIME_H__
#define TERMINA__SHARED__TIME_H__

#include "config.h"

#include <termina.h>


/**
 * @brief Adds one time value to another.
 *
 * @param[in,out] lhs  Time value to increment.
 * @param[in]     rhs  Increment.
 */
void termina__shared__add_timeval(TimeVal * const lhs, const TimeVal * const rhs);

/**
 * @brief Number of ticks per second.
 *
 * @return The number of ticks per second.
 */
static inline uint64_t termina__shared__time__ticks_per_sec(void) {
    return 1000000U / TERMINA__TIME__MICROSECONDS_PER_TICK;
}

/**
 * @brief Gets the time elapsed since boot.
 *
 * Each operating system implements this function.
 *
 * @param[out] uptime  Time elapsed since boot.
 */
void termina__os__time__clock_get_uptime(TimeVal * const uptime);

/**
 * @brief Blocks the calling task for a given time.
 *
 * Each operating system implements this function.
 *
 * @param[in] time_val  Time during which the task is blocked.
 */
void termina__os__time__delay_in(const TimeVal * const time_val);

#endif // TERMINA__SHARED__TIME_H__