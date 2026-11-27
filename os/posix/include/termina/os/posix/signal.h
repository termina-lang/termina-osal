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
 * The main task calls this function before any other task is created, so that
 * the other threads inherit the signal mask. The function also installs the
 * handlers of `SIGALRM`, `SIGUSR2` and the fault signals.
 */
void termina__posix__signal__init(void);

/**
 * @brief Increments the blocking nesting level and, when it was 0, blocks the
 *        signals of `signal_set` for the current task.
 *
 * The task receives no signals until they are unblocked. The only exceptions
 * are `SIGINT`, `SIGTERM`, `SIGSEGV`, `SIGBUS`, `SIGFPE` and `SIGILL`, which
 * are always unblocked.
 */
void termina__posix__signal__disable(void);

/**
 * @brief Decrements the blocking nesting level and, when it reaches 0,
 *        unblocks the signals of `signal_set` for the current task.
 */
void termina__posix__signal__enable(void);

#endif // TERMINA__OS__POSIX__SIGNAL_H__