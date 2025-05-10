#ifndef __TERMINA__EXEC_H__
#define __TERMINA__EXEC_H__

/**
 * \brief Reboots the system.
 *
 * This function is called when the system must reboot. 
 * The function never returns to its caller.
 */
_Noreturn void __termina_exec__reboot();

#endif // __TERMINA__EXEC_H__
