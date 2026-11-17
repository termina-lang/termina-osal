#ifndef TERMINA__COVERAGE_H__
#define TERMINA__COVERAGE_H__

#include <termina/types.h>

/**
 * \brief Placement of the arrays of the coverage: the section TERMINA__COVERAGE__SECTION, or the .bss.
 */
#if defined(TERMINA__COVERAGE__SECTION)
#define TERMINA__COVERAGE__PLACEMENT __attribute__((section(TERMINA__COVERAGE__SECTION)))
#else
#define TERMINA__COVERAGE__PLACEMENT
#endif

/**
 * \brief Witness of a decision or a condition of the coverage.
 *
 * @param[out] flags  The row of the witness: [0] for the value true, [1] for
 *                    the value false.
 * @param[in]  v      The value of the decision or the condition.
 *
 * @return The value.
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
