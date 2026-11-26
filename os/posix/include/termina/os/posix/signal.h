/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Signal handling of the POSIX emulation, which plays the role of the
 *        interrupts.
 */

#ifndef TERMINA__OS__POSIX__SIGNAL_H__
#define TERMINA__OS__POSIX__SIGNAL_H__

#include <termina.h>

#include <pthread.h>
#include <signal.h>

/** @brief Set of the signals that the emulation blocks and unblocks. */
extern sigset_t signal_set;

/** @brief Nesting level of the calls that block the signals. */
extern uint32_t termina__posix__blocking_nesting_level;

/**
 * @brief Initializes the signal handling mechanism.
 *
 * The main task must call this function before any other task is created, so
 * that the other tasks inherit the signal mask and the `SIGALRM` handler.
 */
void termina__posix__signal__init(void);

/**
 * @brief Blocks all the signals for the current task.
 *
 * The task receives no signals until they are unblocked. The only exceptions
 * are `SIGINT`, `SIGTERM`, `SIGSEGV`, `SIGBUS`, `SIGFPE` and `SIGILL`, which
 * are always unblocked.
 */
void termina__posix__signal__disable(void);

/**
 * @brief Unblocks all the signals for the current task.
 * 
 * The task receives all the signals that are sent to it.
 */
void termina__posix__signal__enable(void);

#endif // TERMINA__OS__POSIX__SIGNAL_H__