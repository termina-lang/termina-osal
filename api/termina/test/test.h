#ifndef TERMINA__TEST__TEST_H__
#define TERMINA__TEST__TEST_H__

#include <stddef.h>
#include <stdint.h>

/**
 * \brief Version of the format of the record.
 */
#define TERMINA__TEST__VERSION 1U

/**
 * \brief The scenario of a concurrent test has called finish().
 */
#define TERMINA__TEST__FLAG_FINISHED 0x1U

/**
 * \brief A record did not fit in the area and was not written.
 */
#define TERMINA__TEST__FLAG_OVERFLOW 0x2U

/**
 * \brief Header of the record of a test.
 *
 * The runner reads it after the run: on a target from the object that the
 * generated C defines, on posix from the start of the file it creates. The
 * runner writes selected_case before the run, and the runtime never touches
 * it.
 */
typedef struct {

    uint8_t   magic[8];       /**< "TRMTEST\0" */
    uint16_t  version;        /**< TERMINA__TEST__VERSION */
    uint16_t  flags;          /**< TERMINA__TEST__FLAG_* */
    uint32_t  stamp;          /**< Fingerprint of the descriptor. */
    uint32_t  capacity;       /**< Bytes of the record area. */
    uint32_t  write_offset;   /**< Bytes of the area already written. */
    uint32_t  selected_case;  /**< 0 for all the cases, cases from 1. */
    uint32_t  cases_ended;
    uint32_t  checks_failed;
    uint32_t  checks_passed;
    size_t    last_step;      /**< Last step(n) of the current case or scenario. */
    uintptr_t anchor;         /**< Run-time address of termina__test__stamp. */

} termina__test__header_t;

/**
 * \brief Kinds of record, written as the first byte of each one.
 */
typedef enum {

    termina__test__tag__case_begin = 1,
    termina__test__tag__case_end = 2,
    termina__test__tag__finish = 3,
    termina__test__tag__end = 4,
    termina__test__tag__exception = 5,
    termina__test__tag__fail_check = 6,
    termina__test__tag__fail_check_eq_u8 = 7,
    termina__test__tag__fail_check_eq_u16 = 8,
    termina__test__tag__fail_check_eq_u32 = 9,
    termina__test__tag__fail_check_eq_u64 = 10,
    termina__test__tag__fail_check_eq_i8 = 11,
    termina__test__tag__fail_check_eq_i16 = 12,
    termina__test__tag__fail_check_eq_i32 = 13,
    termina__test__tag__fail_check_eq_i64 = 14,
    termina__test__tag__fail_check_eq_usize = 15,
    termina__test__tag__fail_check_eq_bool = 16,
    termina__test__tag__fail_check_eq_char = 17,
    termina__test__tag__fail_check_elapsed = 18,
    termina__test__tag__fail_fail = 19,
    termina__test__tag__elapsed = 20

} termina__test__tag_t;

/**
 * \brief Fingerprint of the descriptor, defined by the generated C.
 */
extern const uint32_t termina__test__stamp;

/**
 * \brief Bytes of the record area, defined by the generated C.
 */
extern const uint32_t termina__test__capacity;

/**
 * \brief Header of the record on a target, defined by the generated C.
 */
extern termina__test__header_t termina__test__header;

/**
 * \brief Record area on a target, defined by the generated C.
 */
extern uint8_t termina__test__area[];

/**
 * \brief Initializes the record of the test.
 *
 * The main function of the platform calls it before termina__app__init. The
 * runner of a target stops here to write selected_case.
 */
void termina__test__init(void);

/**
 * \brief Tells whether the harness has to run a case.
 *
 * @param[in]  test_case  the number of the case, from 1.
 *
 * @return true when the runner selected every case or this one.
 */
_Bool termina__test__selected(const uint16_t test_case);

/**
 * \brief Starts a case.
 *
 * Resets the last step and the count of checks of the case, and writes the
 * CASE_BEGIN record.
 *
 * @param[in]  test_case  the number of the case, from 1.
 */
void termina__test__case_begin(const uint16_t test_case);

/**
 * \brief Ends the current case.
 *
 * Writes the CASE_END record with the number of checks that the case ran.
 */
void termina__test__case_end(void);

/**
 * \brief Sets the test clock to zero.
 *
 * The reset of a unit test calls it before each case.
 */
void termina__test__clock__reset(void);

/**
 * \brief Ends the test.
 *
 * Writes the END record and stops the machine without restarting it. The
 * runner of a target stops here.
 */
_Noreturn void termina__test__end(void);

#endif // TERMINA__TEST__TEST_H__
