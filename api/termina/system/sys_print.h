/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Print procedures of the system entry.
 */

#ifndef TERMINA__SYSTEM__SYS_PRINT_H__
#define TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>
#include <termina/prelude.h>
#include <termina/float.h>

/**
 * @brief Size of the print output buffer, 256 characters unless the build
 *        defines it.
 */
#ifndef TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE
#define TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE 256
#endif

/**
 * @brief Prints a string.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] str            Array of characters to print.
 */
extern void SystemEntry__print(const termina__event_t * const termina__ev,
                               void * const termina__this,
                               const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * @brief Prints a string followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] str            Array of characters to print.
 */
extern void SystemEntry__println(const termina__event_t * const termina__ev,
                                 void * const termina__this,
                                 const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]);

/**
 * @brief Prints a character.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] c              Character to print.
 */
extern void SystemEntry__print_char(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const char c);

/**
 * @brief Prints a character followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] c              Character to print.
 */
extern void SystemEntry__println_char(const termina__event_t * const termina__ev,
                                      void * const termina__this,
                                      const char c);

/**
 * @brief Prints an unsigned 8-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_u8(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const uint8_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 8-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_u8(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const uint8_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 16-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_u16(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint16_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 16-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_u16(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const uint16_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 32-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_u32(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint32_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 32-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_u32(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const uint32_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 64-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_u64(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const uint64_t value, const SysPrintBase base);

/**
 * @brief Prints an unsigned 64-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_u64(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const uint64_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 8-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_i8(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  const int8_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 8-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_i8(const termina__event_t * const termina__ev,
                                    void * const termina__this,
                                    const int8_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 16-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_i16(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int16_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 16-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_i16(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const int16_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 32-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_i32(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int32_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 32-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_i32(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const int32_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 64-bit integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_i64(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const int64_t value, const SysPrintBase base);

/**
 * @brief Prints a signed 64-bit integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_i64(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const int64_t value, const SysPrintBase base);

/**
 * @brief Prints a usize integer.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__print_usize(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const size_t value, const SysPrintBase base);

/**
 * @brief Prints a usize integer followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Integer to print.
 * @param[in] base           Base in which the integer is printed.
 */
extern void SystemEntry__println_usize(const termina__event_t * const termina__ev,
                                       void * const termina__this,
                                       const size_t value, const SysPrintBase base);

/**
 * @brief Prints a 32-bit floating point number.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Floating-point number to print.
 */
extern void SystemEntry__print_f32(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const float32_t value);

/**
 * @brief Prints a 32-bit floating point number followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Floating-point number to print.
 */
extern void SystemEntry__println_f32(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const float32_t value);

/**
 * @brief Prints a 64-bit floating point number.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Floating-point number to print.
 */
extern void SystemEntry__print_f64(const termina__event_t * const termina__ev,
                                   void * const termina__this,
                                   const float64_t value);

/**
 * @brief Prints a 64-bit floating point number followed by a new line.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the system entry object.
 * @param[in] value          Floating-point number to print.
 */
extern void SystemEntry__println_f64(const termina__event_t * const termina__ev,
                                     void * const termina__this,
                                     const float64_t value);


#endif // TERMINA__SYSTEM__SYS_PRINT_H__
