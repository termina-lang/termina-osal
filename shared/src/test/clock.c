#include <termina.h>
#include <termina/shared/test.h>
#include <termina/shared/time.h>

/**
 * \brief The test_clock object.
 */
termina__test__entry_t test_clock;

static TimeVal termina__shared__test__clock = { .tv_sec = 0U, .tv_usec = 0U };

void TestClockEntry__advance(const termina__event_t * const termina__ev,
                             void * const termina__this,
                             const TimeVal dt) {

    termina__test__entry_t * self = (termina__test__entry_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    termina__shared__add_timeval(&termina__shared__test__clock, &dt);

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

}

void termina__test__clock__reset(void) {

    termina__shared__test__clock.tv_sec = 0U;
    termina__shared__test__clock.tv_usec = 0U;

    return;

}

void termina__shared__test__clock_get(TimeVal * const now) {

    *now = termina__shared__test__clock;

    return;

}
