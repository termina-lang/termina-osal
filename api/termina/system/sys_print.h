#ifndef __TERMINA__SYSTEM__SYS_PRINT_H__
#define __TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Print a string.
 *
 * @param[in] str the array of characters to print.
 */
extern void SystemEntry__print(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);

/**
 * \brief Print a string followed by a new line.
 *
 * @param[in] str the array of characters to print.
 */
extern void SystemEntry__println(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);

/**
 * \brief Print a character.
 *
 * @param[in] value the character to print.
 */
extern void SystemEntry__print_char(const char value);

/**
 * \brief Print a character followed by a newline.
 *
 * @param[in] value the character to print.
 */
extern void SystemEntry__println_char(const char value);

/**
 * \brief Print an unsigned 8-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u8(const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u8(const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u16(const uint16_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer followed by a newline
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u16(const uint16_t value, const SysPrintBase base);
    
/**
 * \brief Print an unsigned 32-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u32(const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 32-bit integer followed by a newline:
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u32(const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u64(const uint64_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer followed by a newline
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u64(const uint64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i8(const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i8(const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i16(const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i16(const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i32(const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i32(const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i64(const int64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i64(const int64_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_usize(const size_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_usize(const size_t value, const SysPrintBase base);


#endif // __TERMINA__SYSTEM__SYS_PRINT_H__
