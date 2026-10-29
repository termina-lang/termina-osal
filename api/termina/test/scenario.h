#ifndef TERMINA__TEST__SCENARIO_H__
#define TERMINA__TEST__SCENARIO_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/test/checks.h>

/**
 * \brief The test_scenario object.
 */
extern termina__test__entry_t test_scenario;

/**
 * \brief Creates the queue on which the harness of a concurrent test waits
 *        for finish(), and opens the scenario as case 1 of the record.
 *
 * @param[in]  msg_queue_id  the identifier of the queue, which the generated
 *                           config.h reserves.
 * @param[out] status        the result of the creation.
 */
void termina__test__scenario__init(const termina__id_t msg_queue_id,
                                   termina__error_code_t * const status);

/**
 * \brief Ends the test when the current action ends.
 *
 * The first call records FINISH, sets the finished flag of the header and
 * wakes the harness; every later call does nothing.
 *
 * @param[in] termina__ev    the event that is being processed when finish() is called.
 * @param[in] termina__this  the test_scenario object.
 */
extern void TestScenarioEntry__finish(const termina__event_t * const termina__ev,
                                      void * const termina__this);

/**
 * \brief Body of the harness of a concurrent test.
 *
 * Waits for finish(), which the harness, at the lowest priority, only sees
 * when every other task is blocked. Then disables the interrupts, ends the
 * scenario and ends the test.
 */
_Noreturn void termina__test__scenario__harness(void);

#endif // TERMINA__TEST__SCENARIO_H__
