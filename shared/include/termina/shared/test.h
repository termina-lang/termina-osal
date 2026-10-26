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
