#ifndef TERMINA__TEST__CLOCK_H__
#define TERMINA__TEST__CLOCK_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/test/checks.h>

/**
 * \brief The test_clock object.
 */
extern termina__test__entry_t test_clock;

/**
 * \brief Moves the test clock forward.
 *
 * @param[in] termina__ev    the event that is being processed when the clock is advanced.
 * @param[in] termina__this  the test_clock object.
 * @param[in] dt             the time to add to the clock.
 */
extern void TestClockEntry__advance(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const TimeVal dt);

#endif // TERMINA__TEST__CLOCK_H__
