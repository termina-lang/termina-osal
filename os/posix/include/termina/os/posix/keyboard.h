#ifndef TERMINA__OS__POSIX__KEYBOARD_H__
#define TERMINA__OS__POSIX__KEYBOARD_H__

#include <termina.h>

/**
 * @brief Initialize the POSIX keyboard driver.
 *
 * This function configure the standard input to be non-blocking.
 */
void termina__posix__keyboard__init(void);

/**
 * @brief Initialize the POSIX keyboard IRQ handler.
 */
void termina__posix__keyboard__irq_init(int32_t * const status);

/**
 * @brief The POSIX keyboard IRQ handler.
 */
void termina__posix__keyboard__irq_handler(int signum);

#endif // TERMINA__OS__POSIX__KEYBOARD_H__