#include <termina.h>
#include <termina/shared/exec.h>
#include <termina/shared/test.h>

/**
 * \brief The test_scenario object.
 */
termina__test__entry_t test_scenario;

static termina__id_t termina__shared__test__harness_queue = TERMINA__ID__INVALID;

void termina__test__scenario__init(const termina__id_t msg_queue_id,
                                   termina__error_code_t * const status) {

    termina__shared__test__harness_queue = msg_queue_id;

    termina__msg_queue__init(msg_queue_id, sizeof(uint8_t), 1U, status);

    // The scenario is the only case, and it is open from before the first task
    termina__test__case_begin(1U);

    return;

}

void TestScenarioEntry__finish(const termina__event_t * const termina__ev,
                               void * const termina__this) {

    termina__test__entry_t * self = (termina__test__entry_t * const)termina__this;

    const void * const where = __builtin_return_address(0);

    termina__error_code_t status = termina__error__none;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    // The flag keeps the queue of one element from receiving a second message
    if (termina__shared__test__finish()) {
        const uint8_t message = 0U;
        termina__msg_queue__send(termina__shared__test__harness_queue, &message, &status);
    }

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

    if (termina__error__none != status) {
        termina__except__runtime_failure((size_t)where,
                                         termina__runtime_operation__test_finish,
                                         status);
    }

}

_Noreturn void termina__test__scenario__harness(void) {

    termina__error_code_t status = termina__error__none;

    uint8_t message = 0U;

    termina__msg_queue__recv(termina__shared__test__harness_queue, &message, &status);

    if (termina__error__none != status) {
        termina__except__runtime_failure(0U, termina__runtime_operation__test_finish,
                                         status);
    }

    // With the interrupts disabled no task or timer writes in the middle of the end
    termina__os__exec__quiesce();

    termina__test__case_end();

    termina__test__end();

}
