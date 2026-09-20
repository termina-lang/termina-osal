#ifndef TERMINA__SHARED__LOCK_H__
#define TERMINA__SHARED__LOCK_H__

#include <termina.h>

/**
 * \brief Task interrupt lock. This function is used to protect shared
 *        resources from concurrent access by tasks and event handlers.
 * 
 * @return The lock that must be used to unlock the resource. 
 */
termina__lock_t termina__os__irq_lock(void);

/**
 * \brief Unlocks an interrupt lock. This function must receive as argument
 *        the lock that was previously returned when locking.  
 * 
 * @param[in] irq_lock the lock. The function will store in this argument the
 *                     lock that must be used to unlock the resource. 
 */
void termina__os__irq_unlock(termina__lock_t irq_lock);


#endif // TERMINA__SHARED__LOCK_H__