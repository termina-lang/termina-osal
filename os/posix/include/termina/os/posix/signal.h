#ifndef __TERMINA__OS__POSIX__SIGNAL_H__
#define __TERMINA__OS__POSIX__SIGNAL_H__

#include <termina.h>

#include <pthread.h>
#include <signal.h>

extern sigset_t signal_set;

extern uint32_t __posix_blocking_nesting_level;

/**
 * \brief Initializes the signal handling mechanism.
 *
 * This function must be called by the main task before any other task is
 * created so that the rest of the tasks inherit the signal mask and the
 * SIG_ALRM signal handler.
 */
void __posix_signal__init(void);

/**
 * \brief Blocks all the signals for the current task.
 *
 * This function blocks all the signals for the current task. This means that
 * the task will not receive any signals until they are unblocked. The only
 * exception is the SIGINT signal, which is always unblocked.
 */
void __posix_signal__disable(void);

/**
 * \brief Unblocks all the signals for the current task.
 * 
 * This function unblocks all the signals for the current task. This means that
 * the task will receive all the signals that are sent to it.
 */
void __posix_signal__enable(void);

#endif // __TERMINA__OS__POSIX__SIGNAL_H__