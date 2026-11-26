/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Placement of the coverage flags and witness of the decisions and
 *        conditions.
 */

#ifndef TERMINA__COVERAGE_H__
#define TERMINA__COVERAGE_H__

#include <termina/types.h>

/**
 * @brief Placement of the coverage arrays: the section
 *        `TERMINA__COVERAGE__SECTION` if it is defined, or `.bss` otherwise.
 */
#if defined(TERMINA__COVERAGE__SECTION)
#define TERMINA__COVERAGE__PLACEMENT __attribute__((section(TERMINA__COVERAGE__SECTION)))
#else
#define TERMINA__COVERAGE__PLACEMENT
#endif

/**
 * @brief Records the value of a decision or a condition in its coverage flags.
 *
 * @param[out] flags  Flags of the decision or condition: `[0]` for the value
 *                    true, `[1]` for the value false.
 * @param[in]  v      Value of the decision or condition.
 *
 * @return The value `v`.
 */
static inline _Bool termina__cov__w(volatile uint8_t flags[2U], const _Bool v) {

    if (v) {
        flags[0U] = 1U;
    } else {
        flags[1U] = 1U;
    }

    return v;

}

#endif // TERMINA__COVERAGE_H__
