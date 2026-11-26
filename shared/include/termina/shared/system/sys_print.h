/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Print operations, which each operating system implements.
 */

#ifndef TERMINA__SHARED__SYSTEM__SYS_PRINT_H__
#define TERMINA__SHARED__SYSTEM__SYS_PRINT_H__

#include <termina.h>

/**
 * @brief Prints a string.
 *
 * @param[in] str  Array of characters to print.
 */
extern void termina__os__sys_print__print(const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * @brief Prints a string followed by a new line.
 *
 * @param[in] str  Array of characters to print.
 */
extern void termina__os__sys_print__println(const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * @brief Prints a character.
 *
 * @param[in] c  Character to print.
 */
extern void termina__os__sys_print__print_char(const char c);

/**
 * @brief Prints a character followed by a new line.
 *
 * @param[in] c  Character to print.
 */
extern void termina__os__sys_print__println_char(const char c);

/**
 * @brief Prints an unsigned 8-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_u8(const uint8_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_u8(const uint8_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 16-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_u16(const uint16_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 16-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_u16(const uint16_t value, const SysPrintBase base);
    
/**
 * @brief Prints an unsigned 32-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_u32(const uint32_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 32-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_u32(const uint32_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 64-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_u64(const uint64_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 64-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_u64(const uint64_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 8-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_i8(const int8_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 8-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_i8(const int8_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 16-bit integer.
 * 
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_i16(const int16_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 16-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_i16(const int16_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 32-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_i32(const int32_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 32-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_i32(const int32_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 64-bit integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_i64(const int64_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 64-bit integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_i64(const int64_t value, const SysPrintBase base);

/**
 * @brief Prints a usize integer.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__print_usize(const size_t value, const SysPrintBase base);

/**
 * @brief Prints a usize integer followed by a new line.
 *
 * @param[in] value  Integer to print.
 * @param[in] base   Base in which the integer is printed.
 */
extern void termina__os__sys_print__println_usize(const size_t value, const SysPrintBase base);

/**
 * @brief Prints a 32-bit floating point number.
 *
 * @param[in] value  Floating-point number to print.
 */
extern void termina__os__sys_print__print_f32(const float32_t value);

/**
 * @brief Prints a 32-bit floating point number followed by a new line.
 *
 * @param[in] value  Floating-point number to print.
 */
extern void termina__os__sys_print__println_f32(const float32_t value);

/**
 * @brief Prints a 64-bit floating point number.
 *
 * @param[in] value  Floating-point number to print.
 */
extern void termina__os__sys_print__print_f64(const float64_t value);

/**
 * @brief Prints a 64-bit floating point number followed by a new line.
 *
 * @param[in] value  Floating-point number to print.
 */
extern void termina__os__sys_print__println_f64(const float64_t value);


#endif // TERMINA__SHARED__SYSTEM__SYS_PRINT_H__
