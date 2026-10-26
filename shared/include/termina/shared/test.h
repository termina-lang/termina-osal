#ifndef TERMINA__SHARED__TEST_H__
#define TERMINA__SHARED__TEST_H__

#include <termina.h>

/**
 * \brief Writes a record in the area of the test.
 *
 * The record is written whole or not at all: when it does not fit, the
 * function sets TERMINA__TEST__FLAG_OVERFLOW and writes nothing.
 *
 * @param[in]  record  the bytes of the record, starting with its tag.
 * @param[in]  size    the number of bytes of the record.
 */
void termina__shared__test__write(const uint8_t * const record, const size_t size);

/**
 * \brief Counts a check that passed.
 */
void termina__shared__test__pass(void);

/**
 * \brief Counts a check that failed and writes its record.
 *
 * The record carries the tag, the last step, the address of the call and, when
 * size is not zero, the value obtained and the value expected.
 *
 * @param[in]  tag       the tag of the failure.
 * @param[in]  where     the return address of the check.
 * @param[in]  actual    the value obtained, or NULL.
 * @param[in]  expected  the value expected, or NULL.
 * @param[in]  size      the bytes of each value, at most sizeof(TimeVal).
 */
void termina__shared__test__fail(const termina__test__tag_t tag,
                                 const void * const where,
                                 const void * const actual,
                                 const void * const expected,
                                 const size_t size);

/**
 * \brief Sets the last step of the current case or scenario.
 *
 * @param[in]  n  the step.
 */
void termina__shared__test__step(const size_t n);

/**
 * \brief Gets the header and the area of the record.
 *
 * @param[out]  header  pointer to the header of the record.
 * @param[out]  area    pointer to the start of the record area.
 */
void termina__os__test__open(termina__test__header_t ** const header,
                             uint8_t ** const area);

/**
 * \brief Stops the machine without restarting it.
 */
_Noreturn void termina__os__test__halt(void);

#endif // TERMINA__SHARED__TEST_H__
