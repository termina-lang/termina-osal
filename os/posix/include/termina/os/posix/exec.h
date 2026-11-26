/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Debug stop of the POSIX emulation before a reboot.
 */

#ifndef TERMINA__OS__POSIX__EXEC_H__
#define TERMINA__OS__POSIX__EXEC_H__

/**
 * @brief Stops the program before it restarts, in the debug profile.
 *
 * The function prints the stack and raises `SIGTRAP`, which stops the
 * program under gdb and terminates it when no debugger is attached. In the
 * release profile it does nothing.
 */
void termina__posix__exec__debug_stop(void);

#endif // TERMINA__OS__POSIX__EXEC_H__
