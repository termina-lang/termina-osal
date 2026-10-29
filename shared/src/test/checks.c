#include <termina.h>
#include <termina/shared/test.h>

/**
 * \brief The test_checks object.
 */
termina__test__entry_t test_checks;

static void termina__test__checks__verdict(const termina__event_t * const termina__ev,
                                           void * const termina__this,
                                           const _Bool passed,
                                           const termina__test__tag_t tag,
                                           const void * const where,
                                           const void * const actual,
                                           const void * const expected,
                                           const size_t size) {

    termina__test__entry_t * self = (termina__test__entry_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    if (passed) {
        termina__shared__test__pass();
    } else {
        termina__shared__test__fail(tag, where, actual, expected, size);
    }

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

}

void TestChecksEntry__check(const termina__event_t * const termina__ev,
                            void * const termina__this,
                            const _Bool cond) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, cond,
                                   termina__test__tag__fail_check, where,
                                   NULL, NULL, 0U);

}

void TestChecksEntry__check_eq_u8(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const uint8_t actual, const uint8_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_u8, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_u16(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint16_t actual, const uint16_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_u16, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_u32(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint32_t actual, const uint32_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_u32, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_u64(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint64_t actual, const uint64_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_u64, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_i8(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const int8_t actual, const int8_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_i8, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_i16(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int16_t actual, const int16_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_i16, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_i32(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int32_t actual, const int32_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_i32, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_i64(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int64_t actual, const int64_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_i64, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_usize(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const size_t actual, const size_t expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_usize, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_bool(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const _Bool actual, const _Bool expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_bool, where,
                                   &actual, &expected, sizeof(actual));

}

void TestChecksEntry__check_eq_char(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const char actual, const char expected) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, actual == expected,
                                   termina__test__tag__fail_check_eq_char, where,
                                   &actual, &expected, sizeof(actual));

}

static void termina__test__checks__elapsed(const TimeVal * const now,
                                           const TimeVal * const t0,
                                           TimeVal * const elapsed) {

    elapsed->tv_sec = 0U;
    elapsed->tv_usec = 0U;

    // A t0 later than now counts as no time elapsed
    if (now->tv_sec > t0->tv_sec) {

        if (now->tv_usec >= t0->tv_usec) {
            elapsed->tv_sec = now->tv_sec - t0->tv_sec;
            elapsed->tv_usec = now->tv_usec - t0->tv_usec;
        } else {
            elapsed->tv_sec = (now->tv_sec - t0->tv_sec) - 1U;
            elapsed->tv_usec = (now->tv_usec + 1000000U) - t0->tv_usec;
        }

    } else if ((now->tv_sec == t0->tv_sec) && (now->tv_usec > t0->tv_usec)) {

        elapsed->tv_usec = now->tv_usec - t0->tv_usec;

    } else {

        // No time elapsed

    }

}

static _Bool termina__test__checks__timed(void) {

#if defined(TERMINA__TEST__CLOCK)
    return true;
#else
    return termina__os__test__has_timing();
#endif

}

void TestChecksEntry__check_elapsed(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const TimeVal t0,
                                    const TimeVal max) {

    termina__test__entry_t * self = (termina__test__entry_t * const)termina__this;

    const void * const where = __builtin_return_address(0);

    TimeVal now = { .tv_sec = 0U, .tv_usec = 0U };
    TimeVal elapsed = { .tv_sec = 0U, .tv_usec = 0U };

    SystemEntry__clock_get_uptime(termina__ev, &system_entry, &now);
    termina__test__checks__elapsed(&now, &t0, &elapsed);

    const _Bool exceeded = (elapsed.tv_sec > max.tv_sec)
        || ((elapsed.tv_sec == max.tv_sec) && (elapsed.tv_usec > max.tv_usec));

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    if (!termina__test__checks__timed()) {
        termina__shared__test__measure(termina__test__tag__elapsed, where,
                                       &elapsed, &max, sizeof(TimeVal));
    } else if (exceeded) {
        termina__shared__test__fail(termina__test__tag__fail_check_elapsed, where,
                                    &elapsed, &max, sizeof(TimeVal));
    } else {
        termina__shared__test__pass();
    }

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

}

void TestChecksEntry__fail(const termina__event_t * const termina__ev,
                           void * const termina__this) {

    const void * const where = __builtin_return_address(0);

    termina__test__checks__verdict(termina__ev, termina__this, false,
                                   termina__test__tag__fail_fail, where,
                                   NULL, NULL, 0U);

}

void TestChecksEntry__step(const termina__event_t * const termina__ev,
                           void * const termina__this,
                           const size_t n) {

    termina__test__entry_t * self = (termina__test__entry_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    termina__shared__test__step(n);

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type,
                               termina__lock);

}
