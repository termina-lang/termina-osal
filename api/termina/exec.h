#ifndef TERMINA__EXEC_H__
#define TERMINA__EXEC_H__

/**
 * \brief Reboots the system.
 *
 * This function is called when the system must reboot. 
 * The function never returns to its caller.
 */
_Noreturn void termina__exec__reboot(void);

#endif // TERMINA__EXEC_H__
