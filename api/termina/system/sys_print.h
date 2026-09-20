#ifndef TERMINA__SYSTEM__SYS_PRINT_H__
#define TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/float.h>

#include "config.h"

/**
 * \brief Size of the print output buffer. If not specified, the default value
 *        of 256 characters is used.
 */
#ifndef TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE
#define TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE 256
#endif

/**
 * \brief Print a string.
 *
 * @param[in] termina__ev  the event that is being processed when the print is requested.
 * @param[in] str   the array of characters to print.
 */
extern void SystemEntry__print(const termina__event_t * const termina__ev,
                               const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * \brief Print a string followed by a new line.
 *
 * @param[in] termina__ev  the event that is being processed when the print is requested.
 * @param[in] str   the array of characters to print.
 */
extern void SystemEntry__println(const termina__event_t * const termina__ev,
                                 const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * \brief Print a character.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the character to print.
 */
extern void SystemEntry__print_char(const termina__event_t * const termina__ev,
                                    const char value);

/**
 * \brief Print a character followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the character to print.
 */
extern void SystemEntry__println_char(const termina__event_t * const termina__ev,
                                      const char value);

/**
 * \brief Print an unsigned 8-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u8(const termina__event_t * const termina__ev,
                                  const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u8(const termina__event_t * const termina__ev,
                                    const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u16(const termina__event_t * const termina__ev,
                                   const uint16_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer followed by a newline
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u16(const termina__event_t * const termina__ev,
                                     const uint16_t value, const SysPrintBase base);
    
/**
 * \brief Print an unsigned 32-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u32(const termina__event_t * const termina__ev,
                                   const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 32-bit integer followed by a newline:
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u32(const termina__event_t * const termina__ev,
                                     const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u64(const termina__event_t * const termina__ev,
                                   const uint64_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer followed by a newline
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u64(const termina__event_t * const termina__ev,
                                     const uint64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i8(const termina__event_t * const termina__ev,
                                  const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i8(const termina__event_t * const termina__ev,
                                    const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer.
 * 
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i16(const termina__event_t * const termina__ev,
                                   const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i16(const termina__event_t * const termina__ev,
                                     const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i32(const termina__event_t * const termina__ev,
                                   const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i32(const termina__event_t * const termina__ev,
                                     const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i64(const termina__event_t * const termina__ev,
                                   const int64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i64(const termina__event_t * const termina__ev,
                                     const int64_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_usize(const termina__event_t * const termina__ev,
                                     const size_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer followed by a newline.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_usize(const termina__event_t * const termina__ev,
                                       const size_t value, const SysPrintBase base);

/**
 * \brief Print a 32-bit floating point number.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__print_f32(const termina__event_t * const termina__ev,
                                   const float32_t value);

/**
 * \brief Print a 32-bit floating point number followed by a new line.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__println_f32(const termina__event_t * const termina__ev,
                                     const float32_t value);

/**
 * \brief Print a 64-bit floating point number.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__print_f64(const termina__event_t * const termina__ev,
                                   const float64_t value);

/**
 * \brief Print a 64-bit floating point number followed by a new line.
 *
 * @param[in] termina__ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__println_f64(const termina__event_t * const termina__ev,
                                     const float64_t value);


#endif // TERMINA__SYSTEM__SYS_PRINT_H__
