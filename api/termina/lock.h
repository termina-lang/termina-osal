#ifndef __TERMINA__LOCK_H__
#define __TERMINA__LOCK_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/task.h>
#include <termina/prelude.h>

/**
 * \brief Type used to represent a temporary lock value.
 *
 * This type is returned by a task lock. For the type being, the type is made
 * operating-system-independent.
 */
typedef int32_t __termina_task_lock_t;

/**
 * \brief Type used to represent a temporary lock value.
 *
 * This type is returned by a event lock. For the type being, the type is made
 * operating-system-independent.
 */
typedef int32_t __termina_event_lock_t;

/**
 * \brief Enumeration of the different types of mutex prioirty policies.
 */
typedef enum {

    __TerminaMutexPolicy__Inherit,
    __TerminaMutexPolicy__Ceiling

} __termina_mutex_policy_t;

/**
 * \brief Initializes a mutex. 
 *
 * @param[in]  mutex   the mutex to initialize.
 * @param[out] status  Success if the resource was initialized
 *                     successfully or an error otherwise.
 */
void __termina_mutex__init(const __termina_id_t mutex_id,
                           const __termina_mutex_policy_t policy,
                           const __termina_task_prio_t prio_ceiling,
                           int32_t * const status);

/**
 * \brief Locks a mutex.
 * 
 * This function is used to lock a mutex-protected resource. If the mutex is already
 * locked, the task is blocked until the mutex is unlocked.
 * 
 * The function can be called from tasks only.
 *
 * @param[in]   mutex_id  the identifier of the mutex.
 * @param[out]  status    Success if the resource was locked successfully or an error
 *                        otherwise.  
 */
void __termina_mutex__lock(const __termina_id_t mutex_id,
                           int32_t * status);

/**
 * \brief Unlocks a previously locked mutex-protected resource.
 * 
 * This function is used to unlock a mutex-protected resource. The resource must have
 * been previously locked by the same task.
 * 
 * The function can be called from tasks only.
 *
 * @param[in]  resource_id  the resource.
 * @param[out] status       Success if the resource was unlocked successfully or an error
 *                          otherwise.
 */
void __termina_mutex__unlock(const __termina_id_t mutex_lock_id,
                             int32_t * status);

/**
 * \brief Task lock. This function is used to protect shared
 *        resources from concurrent access by tasks and event handlers.
 *        This function can be called from tasks only.
 * 
 * The function can be called from tasks only.
 *
 * @return The lock that must be used to unlock the resource. 
 */
__termina_task_lock_t __termina_task__lock(void);

/**
 * \brief Unlocks the task lock. This function must receive as argument
 *        the lock that was previously returned when locking.
 *        This function can be called from tasks only.
 * 
 * The function can be called from tasks only.
 *
 * @param[in] task_lock the lock. The function will store in this argument
 *                      the lock that must be used to unlock the resource. 
 */
void __termina_task__unlock(__termina_task_lock_t task_lock);

/**
 * \brief Event lock. This function is used to protect shared
 *        resources from concurrent access by event handlers.
 * 
 * The function can be called from event handlers only.
 *        
 * @return The lock that must be used to unlock the resource. 
 */
__termina_event_lock_t __termina_event__lock(void);

/**
 * \brief Unlocks the event lock. This function must receive as argument
 *        the lock that was previously returned when locking.
 * 
 * The function can be called from event handlers only.
 *        
 * @param[in] event_lock the lock. The function will store in this argument
 *                       the lock that must be used to unlock the resource. 
 */
void __termina_event__unlock(__termina_event_lock_t event_lock);

#endif // __TERMINA__LOCK_H___
