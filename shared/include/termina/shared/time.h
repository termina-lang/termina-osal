#ifndef TERMINA__SHARED__TIME_H__
#define TERMINA__SHARED__TIME_H__

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

#endif // TERMINA__SHARED__TIME_H__