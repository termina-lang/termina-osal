#ifndef TERMINA__SHARED__EXEC_H__
#define TERMINA__SHARED__EXEC_H__

#include <termina.h>

/**
 * \brief Leaves the system with nothing else able to run or interrupt: the
 *        caller keeps running alone and the state is never undone. It is
 *        what the fatal path does before the handler and the reboot, and what
 *        a call to an extern noreturn function does before handing control
 *        over. Implemented for each operating system. It covers the processor
 *        and the operating system, not the peripherals.
 */
void termina__os__exec__quiesce(void);

#endif // TERMINA__SHARED__EXEC_H__
