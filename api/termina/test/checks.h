#ifndef TERMINA__TEST__CHECKS_H__
#define TERMINA__TEST__CHECKS_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Type of the objects of the test resources.
 */
typedef struct {
    termina__resource_lock_type_t _lock_type;
} termina__test__entry_t;

/**
 * \brief The test_checks object.
 */
extern termina__test__entry_t test_checks;

/**
 * \brief Fails when the condition is false.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] cond           the condition.
 */
extern void TestChecksEntry__check(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const _Bool cond);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_u8(const termina__event_t * const termina__ev,
                                         void * const termina__this,
                                         const uint8_t actual, const uint8_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_u16(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const uint16_t actual, const uint16_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_u32(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const uint32_t actual, const uint32_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_u64(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const uint64_t actual, const uint64_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_i8(const termina__event_t * const termina__ev,
                                         void * const termina__this,
                                         const int8_t actual, const int8_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_i16(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const int16_t actual, const int16_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_i32(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const int32_t actual, const int32_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_i64(const termina__event_t * const termina__ev,
                                          void * const termina__this,
                                          const int64_t actual, const int64_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_usize(const termina__event_t * const termina__ev,
                                            void * const termina__this,
                                            const size_t actual, const size_t expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_bool(const termina__event_t * const termina__ev,
                                           void * const termina__this,
                                           const _Bool actual, const _Bool expected);

/**
 * \brief Fails when the two values differ, and records both.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] actual         the value obtained.
 * @param[in] expected       the value expected.
 */
extern void TestChecksEntry__check_eq_char(const termina__event_t * const termina__ev,
                                           void * const termina__this,
                                           const char actual, const char expected);

/**
 * \brief Fails always.
 *
 * @param[in] termina__ev    the event that is being processed when the check is called.
 * @param[in] termina__this  the test_checks object.
 */
extern void TestChecksEntry__fail(const termina__event_t * const termina__ev,
                                  void * const termina__this);

/**
 * \brief Marks the progress of the current case or scenario.
 *
 * Every later failure records the step.
 *
 * @param[in] termina__ev    the event that is being processed when the step is called.
 * @param[in] termina__this  the test_checks object.
 * @param[in] n              the step.
 */
extern void TestChecksEntry__step(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const size_t n);

#endif // TERMINA__TEST__CHECKS_H__
