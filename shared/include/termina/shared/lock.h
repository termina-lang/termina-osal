#ifndef __TERMINA__SHARED__LOCK_H__
#define __TERMINA__SHARED__LOCK_H__

#include <termina.h>

/**
 * \brief Task interrupt lock. This function is used to protect shared
 *        resources from concurrent access by tasks and event handlers.
 *        This function can be called from tasks only.
 * 
 * The function can be called from tasks only.
 *
 * @return The lock that must be used to unlock the resource. 
 */
__termina_lock_t __termina_os_task__irq_lock(void);

/**
 * \brief Unlocks a task interrupt lock. This function must receive as argument
 *        the lock that was previously returned when locking.  This function can be
 *        called from tasks only.
 *
 * The function can be called from tasks only.
 *
 * @param[in] task_irq_lock the lock. The function will store in this argument the
 *                                    lock that must be used to unlock the resource. 
 */
void __termina_os_task__irq_unlock(__termina_lock_t task_irq_lock);

/**
 * \brief Handler interrupt lock. This function is used to protect shared
 *        resources from concurrent access by event handlers.
 *
 * The function can be called from event handlers only.
 *
 * @return The lock that must be used to unlock the resource. 
 */
__termina_lock_t __termina_os_handler__irq_lock(void);

/**
 * \brief Unlocks the handler interrupt lock. This function must receive as
 *        argument the lock that was previously returned when locking.
 *
 * The function can be called from event handlers only.
 *
 * @param[in] handler_irq_lock the lock. The function will store in this argument the
 *                                       lock that must be used to unlock the resource. 
 */
void __termina_os_handler__irq_unlock(__termina_lock_t handler_irq_lock);


#endif // __TERMINA__SHARED__LOCK_H__