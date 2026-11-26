/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Quiescing of the system, which each operating system implements.
 */

#ifndef TERMINA__SHARED__EXEC_H__
#define TERMINA__SHARED__EXEC_H__

#include <termina.h>

/**
 * @brief Leaves the system with nothing else able to run or interrupt.
 *
 * The caller keeps running alone and the state is never undone. The fatal
 * path calls this function before the handler and the reboot, and a call to
 * an `extern noreturn` function calls it before handing control over. Each
 * operating system implements it, and it covers the processor and the
 * operating system, not the peripherals.
 */
void termina__os__exec__quiesce(void);

#endif // TERMINA__SHARED__EXEC_H__
