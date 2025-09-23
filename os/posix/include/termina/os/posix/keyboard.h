#ifndef __TERMINA__OS__POSIX__KEYBOARD_H__
#define __TERMINA__OS__POSIX__KEYBOARD_H__

#include <termina.h>

/**
 * @brief Initialize the POSIX keyboard driver.
 *
 * This function configure the standard input to be non-blocking.
 */
void __posix_keyboard__init(void);

/**
 * @brief Initialize the POSIX keyboard IRQ handler.
 */
void __posix_keyboard__irq_init(int32_t * const status);

#endif // __TERMINA__OS__POSIX__KEYBOARD_H__