#ifndef __TERMINA__SHARED__TIME_H__
#define __TERMINA__SHARED__TIME_H__

#include <termina.h>


/**
 * \brief Increments one timeval by another.
 *
 * @param[inout] rhs    the timeval to be incremented.
 * @param[in] rhs       the increment.
 */
void __termina_shared__add_timeval(TimeVal * const lhs, const TimeVal * const rhs);

#endif // __TERMINA__SHARED__TIME_H__