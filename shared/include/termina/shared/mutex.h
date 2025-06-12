#ifndef __TERMINA__SHARED__MUTEX_H__
#define __TERMINA__SHARED__MUTEX_H__

#include "config.h"

#include <termina.h>

/**
 * \brief Termina mutex initialization data structure.
 *        This structure is used to store mutex data that is defined by the application
 *        architecture itself and known at compile time. The transpiler will generate a
 *        read-only structure with this data for each of the application mutexes.
 */
typedef struct {

    //! Mutex identifier.
    __termina_id_t mutex_id;

    //! Mutex priority policy (inherit or ceiling).
    __termina_mutex_policy_t policy;

    //! Mutex priority ceiling (if used)
    __termina_task_prio_t prio_ceiling;

} __termina_shared_mutex_t;

extern __termina_shared_mutex_t __shared_app_mutex_object_table[__TERMINA_APP_CONFIG_MUTEXES];

/**
 * \brief Gets the mutex object from the mutex identifier.
 * 
 * This function returns the mutex object from the mutex id. It assumes that the
 * mutex id is valid, i.e., it is less than the number of mutexes defined in the
 * application.
 * 
 * @param[in] mutex_id the mutex identifier.
 * 
 * @return the mutex object.
 */
static inline __termina_shared_mutex_t * __termina_shared_mutex__get_mutex(
    const __termina_id_t mutex_id) {

    return &__shared_app_mutex_object_table[mutex_id];

}


/**
 * \brief Initializes a mutex.
 * 
 * This function initializes a mutex. The mutex is initialized with the owner set to
 * __TERMINA_INVALID_ID and the waiting tasks list empty.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was initialized successfully or another
 *                        value in case of an error.      
 */
void __termina_os_mutex__init(const __termina_id_t mutex_id,
                              int32_t * const status);

/**
 * \brief Locks a mutex.
 * 
 * This function locks a mutex. If the mutex is already locked, the task is blocked
 * until the mutex is unlocked.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was locked successfully or another value
 *                        in case of error.
 */
void __termina_os_mutex__lock(const __termina_id_t mutex_id,
                              int32_t * const status);

/**
 * \brief Unlocks a mutex.
 * 
 * This function unlocks a mutex. If there are tasks waiting for the mutex, the task
 * with the highest priority is unblocked.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was unlocked successfully or another value
 *                        in case of error.
 */
void __termina_os_mutex__unlock(const __termina_id_t mutex_id,
                                int32_t * const status);

#endif // __TERMINA__SHARED__MUTEX_H__
