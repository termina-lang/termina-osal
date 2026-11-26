/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Reboot of the system and handover to software outside Termina.
 */

#ifndef TERMINA__EXEC_H__
#define TERMINA__EXEC_H__

/**
 * @brief Reboots the system.
 *
 * The function does not return to its caller.
 */
_Noreturn void termina__exec__reboot(void);

/**
 * @brief Prepares the handover of the system to software outside Termina.
 *
 * The generated code calls it right before a call to an `extern noreturn`
 * function. It leaves nothing else able to run or interrupt, and the state is
 * never undone, so the C code that takes over runs alone, with the interrupts
 * disabled and no services of the operating system.
 */
void termina__exec__handover(void);

#endif // TERMINA__EXEC_H__
