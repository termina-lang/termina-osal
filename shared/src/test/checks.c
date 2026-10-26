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
