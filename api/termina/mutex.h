#ifndef __TERMINA__MUTEX_H__
#define __TERMINA__MUTEX_H__

#include <termina/types.h>
#include <termina/task.h>

/**
 * \brief Enumeration of the different types of mutex prioirty policies.
 */
typedef enum {

    __termina_mutex_policy__inherit,
    __termina_mutex_policy__ceiling

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

#endif // __TERMINA__MUTEX_H__