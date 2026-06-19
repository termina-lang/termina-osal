#ifndef __TERMINA__SYSTEM__SYS_PRINT_H__
#define __TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/float.h>

#include "config.h"

/**
 * \brief Size of the print output buffer. If not specified, the default value
 *        of 256 characters is used.
 */
#ifndef __TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE
#define __TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE 256
#endif

/**
 * \brief Print a string.
 *
 * @param[in] __ev  the event that is being processed when the print is requested.
 * @param[in] str   the array of characters to print.
 */
extern void SystemEntry__print(const __termina_event_t * const __ev,
                               const char str[__TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE]);

/**
 * \brief Print a string followed by a new line.
 *
 * @param[in] __ev  the event that is being processed when the print is requested.
 * @param[in] str   the array of characters to print.
 */
extern void SystemEntry__println(const __termina_event_t * const __ev,
                                 const char str[__TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE]);

/**
 * \brief Print a character.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the character to print.
 */
extern void SystemEntry__print_char(const __termina_event_t * const __ev,
                                    const char value);

/**
 * \brief Print a character followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the character to print.
 */
extern void SystemEntry__println_char(const __termina_event_t * const __ev,
                                      const char value);

/**
 * \brief Print an unsigned 8-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u8(const __termina_event_t * const __ev,
                                  const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u8(const __termina_event_t * const __ev,
                                    const uint8_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u16(const __termina_event_t * const __ev,
                                   const uint16_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 16-bit integer followed by a newline
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u16(const __termina_event_t * const __ev,
                                     const uint16_t value, const SysPrintBase base);
    
/**
 * \brief Print an unsigned 32-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u32(const __termina_event_t * const __ev,
                                   const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 32-bit integer followed by a newline:
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u32(const __termina_event_t * const __ev,
                                     const uint32_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_u64(const __termina_event_t * const __ev,
                                   const uint64_t value, const SysPrintBase base);

/**
 * \brief Print an unsigned 64-bit integer followed by a newline
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_u64(const __termina_event_t * const __ev,
                                     const uint64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i8(const __termina_event_t * const __ev,
                                  const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 8-bit integer followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i8(const __termina_event_t * const __ev,
                                    const int8_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer.
 * 
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i16(const __termina_event_t * const __ev,
                                   const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 16-bit integer followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i16(const __termina_event_t * const __ev,
                                     const int16_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i32(const __termina_event_t * const __ev,
                                   const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 32-bit integer followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i32(const __termina_event_t * const __ev,
                                     const int32_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_i64(const __termina_event_t * const __ev,
                                   const int64_t value, const SysPrintBase base);

/**
 * \brief Print a signed 64-bit integer followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_i64(const __termina_event_t * const __ev,
                                     const int64_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__print_usize(const __termina_event_t * const __ev,
                                     const size_t value, const SysPrintBase base);

/**
 * \brief Print a usize integer followed by a newline.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the integer to print.
 * @param[in] base   the integer representation to use.
 */
extern void SystemEntry__println_usize(const __termina_event_t * const __ev,
                                       const size_t value, const SysPrintBase base);

/**
 * \brief Print a 32-bit floating point number.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__print_f32(const __termina_event_t * const __ev,
                                   const float32_t value);

/**
 * \brief Print a 32-bit floating point number followed by a new line.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__println_f32(const __termina_event_t * const __ev,
                                     const float32_t value);

/**
 * \brief Print a 64-bit floating point number.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__print_f64(const __termina_event_t * const __ev,
                                   const float64_t value);

/**
 * \brief Print a 64-bit floating point number followed by a new line.
 *
 * @param[in] __ev   the event that is being processed when the print is requested.
 * @param[in] value  the floating point number to print.
 */
extern void SystemEntry__println_f64(const __termina_event_t * const __ev,
                                     const float64_t value);


#endif // __TERMINA__SYSTEM__SYS_PRINT_H__
