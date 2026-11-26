/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Procedures of the `test_clock` resource of a test build.
 */

#ifndef TERMINA__TEST__CLOCK_H__
#define TERMINA__TEST__CLOCK_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/test/checks.h>

/**
 * @brief The `test_clock` object.
 */
extern termina__test__entry_t test_clock;

/**
 * @brief Moves the test clock forward.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the `test_clock` object.
 * @param[in] dt             Time to add to the clock.
 */
extern void TestClockEntry__advance(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const TimeVal dt);

#endif // TERMINA__TEST__CLOCK_H__
