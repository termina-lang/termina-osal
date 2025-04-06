#ifndef __TERMINA__SHARED__SYSTEM__SYS_PRINT_H__
#define __TERMINA__SHARED__SYSTEM__SYS_PRINT_H__

#include <termina.h>

/**
 * \brief Prints a zero-terminated string.
 */
void SystemEntry__print(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__print_mutex(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__print_task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__print_event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);

/**
 * \brief Prints a zero-terminated string followed by a newline.
 */
void SystemEntry__println(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__println_mutex(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__println_task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
void SystemEntry__println_event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);

/**
 * \brief Prints a character.
 */
void SystemEntry__print_char(const char value);
void SystemEntry__print_char_mutex(const char value);
void SystemEntry__print_char_task_lock(const char value);
void SystemEntry__print_char_event_lock(const char value);

/**
 * \brief Prints a character followed by a newline.
 */
void SystemEntry__println_char(const char value);
void SystemEntry__println_char_mutex(const char value);
void SystemEntry__println_char_task_lock(const char value);
void SystemEntry__println_char_event_lock(const char value);

/**
 * \brief Prints an unsigned 8-bit integer.
 */
void SystemEntry__print_u8(const uint8_t value, const SysPrintBase base);
void SystemEntry__print_u8_mutex(const uint8_t value, const SysPrintBase base);
void SystemEntry__print_u8_task_lock(const uint8_t value, const SysPrintBase base);
void SystemEntry__print_u8_event_lock(const uint8_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 8-bit integer followed by a newline.
 */
void SystemEntry__println_u8(const uint8_t value, const SysPrintBase base);
void SystemEntry__println_u8_mutex(const uint8_t value, const SysPrintBase base);
void SystemEntry__println_u8_task_lock(const uint8_t value, const SysPrintBase base);
void SystemEntry__println_u8_event_lock(const uint8_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 16-bit integer.
 */
void SystemEntry__print_u16(const uint16_t value, const SysPrintBase base);
void SystemEntry__print_u16_mutex(const uint16_t value, const SysPrintBase base);
void SystemEntry__print_u16_task_lock(const uint16_t value, const SysPrintBase base);
void SystemEntry__print_u16_event_lock(const uint16_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 16-bit integer followed by a newline.
 */
void SystemEntry__println_u16(const uint16_t value, const SysPrintBase base);
void SystemEntry__println_u16_mutex(const uint16_t value, const SysPrintBase base);
void SystemEntry__println_u16_task_lock(const uint16_t value, const SysPrintBase base);
void SystemEntry__println_u16_event_lock(const uint16_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 32-bit integer.
 */
void SystemEntry__print_u32(const uint32_t value, const SysPrintBase base);
void SystemEntry__print_u32_mutex(const uint32_t value, const SysPrintBase base);
void SystemEntry__print_u32_task_lock(const uint32_t value, const SysPrintBase base);
void SystemEntry__print_u32_event_lock(const uint32_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 32-bit integer followed by a newline.
 */
void SystemEntry__println_u32(const uint32_t value, const SysPrintBase base);
void SystemEntry__println_u32_mutex(const uint32_t value, const SysPrintBase base);
void SystemEntry__println_u32_task_lock(const uint32_t value, const SysPrintBase base);
void SystemEntry__println_u32_event_lock(const uint32_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 64-bit integer.
 */
void SystemEntry__print_u64(const uint64_t value, const SysPrintBase base);
void SystemEntry__print_u64_mutex(const uint64_t value, const SysPrintBase base);
void SystemEntry__print_u64_task_lock(const uint64_t value, const SysPrintBase base);
void SystemEntry__print_u64_event_lock(const uint64_t value, const SysPrintBase base);

/**
 * \brief Prints an unsigned 64-bit integer followed by a newline.
 */
void SystemEntry__println_u64(const uint64_t value, const SysPrintBase base);
void SystemEntry__println_u64_mutex(const uint64_t value, const SysPrintBase base);
void SystemEntry__println_u64_task_lock(const uint64_t value, const SysPrintBase base);
void SystemEntry__println_u64_event_lock(const uint64_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 8-bit integer.
 */
void SystemEntry__print_i8(const int8_t value, const SysPrintBase base);
void SystemEntry__print_i8_mutex(const int8_t value, const SysPrintBase base);
void SystemEntry__print_i8_task_lock(const int8_t value, const SysPrintBase base);
void SystemEntry__print_i8_event_lock(const int8_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 8-bit integer followed by a newline.
 */
void SystemEntry__println_i8(const int8_t value, const SysPrintBase base);
void SystemEntry__println_i8_mutex(const int8_t value, const SysPrintBase base);
void SystemEntry__println_i8_task_lock(const int8_t value, const SysPrintBase base);
void SystemEntry__println_i8_event_lock(const int8_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 16-bit integer.
 */
void SystemEntry__print_i16(const int16_t value, const SysPrintBase base);
void SystemEntry__print_i16_mutex(const int16_t value, const SysPrintBase base);
void SystemEntry__print_i16_task_lock(const int16_t value, const SysPrintBase base);
void SystemEntry__print_i16_event_lock(const int16_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 16-bit integer followed by a newline.
 */
void SystemEntry__println_i16(const int16_t value, const SysPrintBase base);
void SystemEntry__println_i16_mutex(const int16_t value, const SysPrintBase base);
void SystemEntry__println_i16_task_lock(const int16_t value, const SysPrintBase base);
void SystemEntry__println_i16_event_lock(const int16_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 32-bit integer.
 */
void SystemEntry__print_i32(const int32_t value, const SysPrintBase base);
void SystemEntry__print_i32_mutex(const int32_t value, const SysPrintBase base);
void SystemEntry__print_i32_task_lock(const int32_t value, const SysPrintBase base);
void SystemEntry__print_i32_event_lock(const int32_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 32-bit integer followed by a newline.
 */
void SystemEntry__println_i32(const int32_t value, const SysPrintBase base);
void SystemEntry__println_i32_mutex(const int32_t value, const SysPrintBase base);
void SystemEntry__println_i32_task_lock(const int32_t value, const SysPrintBase base);
void SystemEntry__println_i32_event_lock(const int32_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 64-bit integer.
 */
void SystemEntry__print_i64(const int64_t value, const SysPrintBase base);
void SystemEntry__print_i64_mutex(const int64_t value, const SysPrintBase base);
void SystemEntry__print_i64_task_lock(const int64_t value, const SysPrintBase base);
void SystemEntry__print_i64_event_lock(const int64_t value, const SysPrintBase base);

/**
 * \brief Prints a signed 64-bit integer followed by a newline.
 */
void SystemEntry__println_i64(const int64_t value, const SysPrintBase base);
void SystemEntry__println_i64_mutex(const int64_t value, const SysPrintBase base);
void SystemEntry__println_i64_task_lock(const int64_t value, const SysPrintBase base);
void SystemEntry__println_i64_event_lock(const int64_t value, const SysPrintBase base);

/**
 * \brief Prints a usize integer.
 */
void SystemEntry__print_usize(const size_t value, const SysPrintBase base);
void SystemEntry__print_usize_mutex(const size_t value, const SysPrintBase base);
void SystemEntry__print_usize_task_lock(const size_t value, const SysPrintBase base);
void SystemEntry__print_usize_event_lock(const size_t value, const SysPrintBase base);

/**
 * \brief Prints a usize integer followed by a newline.
 */
void SystemEntry__println_usize(const size_t value, const SysPrintBase base);
void SystemEntry__println_usize_mutex(const size_t value, const SysPrintBase base);
void SystemEntry__println_usize_task_lock(const size_t value, const SysPrintBase base);
void SystemEntry__println_usize_event_lock(const size_t value, const SysPrintBase base);


#endif // __TERMINA__SHARED__SYSTEM__SYS_PRINT_H__