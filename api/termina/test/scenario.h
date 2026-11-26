/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Scenario of a concurrent test and procedures of the `test_scenario`
 *        resource.
 */

#ifndef TERMINA__TEST__SCENARIO_H__
#define TERMINA__TEST__SCENARIO_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/test/checks.h>

/**
 * @brief The `test_scenario` object.
 */
extern termina__test__entry_t test_scenario;

/**
 * @brief Creates the queue on which the harness of a concurrent test waits
 *        for `finish()`, and opens the scenario as case 1 of the record.
 *
 * @param[in]  msg_queue_id  Identifier of the queue, which the generated
 *                           `config.h` reserves.
 * @param[out] status        Status of the creation of the queue, as
 *                           termina__msg_queue__init() returns it.
 */
void termina__test__scenario__init(const termina__id_t msg_queue_id,
                                   termina__error_code_t * const status);

/**
 * @brief Ends the test when the current action ends.
 *
 * The first call records `FINISH`, sets the finished flag of the header and
 * wakes the harness; every later call does nothing.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the `test_scenario` object.
 */
extern void TestScenarioEntry__finish(const termina__event_t * const termina__ev,
                                      void * const termina__this);

/**
 * @brief Body of the harness of a concurrent test.
 *
 * The harness waits for `finish()`, which it only sees when every other task
 * is blocked, since it runs at the lowest priority. It then disables the
 * interrupts, ends the scenario and ends the test.
 */
_Noreturn void termina__test__scenario__harness(void);

#endif // TERMINA__TEST__SCENARIO_H__
