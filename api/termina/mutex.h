#ifndef TERMINA__MUTEX_H__
#define TERMINA__MUTEX_H__

#include <termina/types.h>
#include <termina/task.h>

/**
 * \brief Mutex locking protocol.
 */
typedef enum {

    MutexProtocol__Ceiling

} termina__enum__MutexProtocol_t;

typedef struct {

    termina__task_prio_t _0;

} termina__enum__MutexProtocol__Ceiling_params_t;

typedef struct {

    termina__enum__MutexProtocol_t _variant;
    termina__enum__MutexProtocol__Ceiling_params_t Ceiling;

} MutexProtocol;

/**
 * \brief Initializes a mutex.
 *
 * @param[in]  mutex_id  the mutex to initialize.
 * @param[in]  protocol  the locking protocol.
 * @param[out] status    Success if the resource was initialized successfully or
 *                       an error otherwise.
 */
void termina__mutex__init(const termina__id_t mutex_id,
                           const MutexProtocol protocol,
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
void termina__mutex__lock(const termina__id_t mutex_id,
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
void termina__mutex__unlock(const termina__id_t mutex_lock_id,
                             int32_t * status);

#endif // TERMINA__MUTEX_H__
