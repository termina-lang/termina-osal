/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Keyboard of the POSIX emulation, whose input is delivered as an
 *        interrupt.
 */

#ifndef TERMINA__OS__POSIX__KEYBOARD_H__
#define TERMINA__OS__POSIX__KEYBOARD_H__

#include <termina.h>

/**
 * @brief Initializes the keyboard driver of the POSIX emulation.
 *
 * The function configures the standard input as non-blocking.
 */
void termina__posix__keyboard__init(void);

/**
 * @brief Installs the handler of the keyboard interrupt and creates the
 *        thread that polls the standard input.
 *
 * @param[out] status  Status of the operation, always `termina__error__none`.
 */
void termina__posix__keyboard__irq_init(termina__error_code_t * const status);

/**
 * @brief Handler of the keyboard interrupt.
 *
 * @param[in] signum  Number of the signal received.
 */
void termina__posix__keyboard__irq_handler(int signum);

#endif // TERMINA__OS__POSIX__KEYBOARD_H__