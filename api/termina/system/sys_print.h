#ifndef __TERMINA__SYSTEM__SYS_PRINT_H__
#define __TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * \brief Print a string.
 *
 * @param[in] str the array of characters to print.
 */
extern void SystemEntry__print(const size_t size, const char str[size]);
extern void SystemEntry__print__mutex_lock(const size_t size, const char str[size]);
extern void SystemEntry__print__task_lock(const size_t size, const char str[size]);
extern void SystemEntry__print__event_lock(const size_t size, const char str[size]);

/**
 * \brief Print a string followed by a new line.
 *
 * @param[in] str the array of characters to print.
 */
extern void SystemEntry__println(const size_t size, const char str[size]);
extern void SystemEntry__println__mutex_lock(const size_t size, const char str[size]);
extern void SystemEntry__println__task_lock(const size_t size, const char str[size]);
extern void SystemEntry__println__event_lock(const size_t size, const char str[size]);

/**
 * \brief Print a character.
 *
 * @param[in] value the character to print.
 */
extern void SystemEntry__print_char(const char value);
extern void SystemEntry__print_char__mutex_lock(const char value);
extern void SystemEntry__print_char__task_lock(const char value);
extern void SystemEntry__print_char__event_lock(const char value);

/**
 * \brief Print a character followed by a newline.
 *
 * @param[in] value the character to print.
 */
extern void SystemEntry__println_char(const char value);
extern void SystemEntry__println_char__mutex_lock(const char value);
extern void SystemEntry__println_char__task_lock(const char value);
extern void SystemEntry__println_char__event_lock(const char value);

/**
 * \brief Print an unsigned 8-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u8(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__print_u8__mutex_lock(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__print_u8__task_lock(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__print_u8__event_lock(const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u8(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__println_u8__mutex_lock(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__println_u8__task_lock(const uint8_t value, const SysPrintBase base);
extern void SystemEntry__println_u8__event_lock(const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u16(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__print_u16__mutex_lock(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__print_u16__task_lock(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__print_u16__event_lock(const uint16_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer followed by a newline
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u16(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__println_u16__mutex_lock(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__println_u16__task_lock(const uint16_t value, const SysPrintBase base);
extern void SystemEntry__println_u16__event_lock(const uint16_t value, const SysPrintBase base);
    
/**
 * \brief Print an unsigned 32-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u32(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__print_u32__mutex_lock(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__print_u32__task_lock(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__print_u32__event_lock(const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 32-bit integer followed by a newline:
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u32(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__println_u32__mutex(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__println_u32__task_lock(const uint32_t value, const SysPrintBase base);
extern void SystemEntry__println_u32__event_lock(const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_u64(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__print_u64__mutex(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__print_u64__task_lock(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__print_u64__event_lock(const uint64_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer followed by a newline
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_u64(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__println_u64__mutex(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__println_u64__task_lock(const uint64_t value, const SysPrintBase base);
extern void SystemEntry__println_u64__event_lock(const uint64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i8(const int8_t value, const SysPrintBase base);
extern void SystemEntry__print_i8__mutex(const int8_t value, const SysPrintBase base);
extern void SystemEntry__print_i8__task_lock(const int8_t value, const SysPrintBase base);
extern void SystemEntry__print_i8__event_lock(const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i8(const int8_t value, const SysPrintBase base);
extern void SystemEntry__println_i8__mutex(const int8_t value, const SysPrintBase base);
extern void SystemEntry__println_i8__task_lock(const int8_t value, const SysPrintBase base);
extern void SystemEntry__println_i8__event_lock(const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i16(const int16_t value, const SysPrintBase base);
extern void SystemEntry__print_i16__mutex(const int16_t value, const SysPrintBase base);
extern void SystemEntry__print_i16__task_lock(const int16_t value, const SysPrintBase base);
extern void SystemEntry__print_i16__event_lock(const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i16(const int16_t value, const SysPrintBase base);
extern void SystemEntry__println_i16__mutex(const int16_t value, const SysPrintBase base);
extern void SystemEntry__println_i16__task_lock(const int16_t value, const SysPrintBase base);
extern void SystemEntry__println_i16__event_lock(const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i32(const int32_t value, const SysPrintBase base);
extern void SystemEntry__print_i32__mutex(const int32_t value, const SysPrintBase base);
extern void SystemEntry__print_i32__task_lock(const int32_t value, const SysPrintBase base);
extern void SystemEntry__print_i32__event_lock(const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i32(const int32_t value, const SysPrintBase base);
extern void SystemEntry__println_i32__mutex(const int32_t value, const SysPrintBase base);
extern void SystemEntry__println_i32__task_lock(const int32_t value, const SysPrintBase base);
extern void SystemEntry__println_i32__event_lock(const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_i64(const int64_t value, const SysPrintBase base);
extern void SystemEntry__print_i64__mutex(const int64_t value, const SysPrintBase base);
extern void SystemEntry__print_i64__task_lock(const int64_t value, const SysPrintBase base);
extern void SystemEntry__print_i64__event_lock(const int64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_i64(const int64_t value, const SysPrintBase base);
extern void SystemEntry__println_i64__mutex(const int64_t value, const SysPrintBase base);
extern void SystemEntry__println_i64__task_lock(const int64_t value, const SysPrintBase base);
extern void SystemEntry__println_i64__event_lock(const int64_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__print_usize(const size_t value, const SysPrintBase base);
extern void SystemEntry__print_usize__mutex(const size_t value, const SysPrintBase base);
extern void SystemEntry__print_usize__task_lock(const size_t value, const SysPrintBase base);
extern void SystemEntry__print_usize__event_lock(const size_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer followed by a newline.
 *
 * @param[in] value the integer to print.
 * @param[in] base  the integer representation to use.
 */
extern void SystemEntry__println_usize(const size_t value, const SysPrintBase base);
extern void SystemEntry__println_usize__mutex(const size_t value, const SysPrintBase base);
extern void SystemEntry__println_usize__task_lock(const size_t value, const SysPrintBase base);
extern void SystemEntry__println_usize__event_lock(const size_t value, const SysPrintBase base);


#endif // __TERMINA__SYSTEM__SYS_PRINT_H__
