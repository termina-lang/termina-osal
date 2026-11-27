/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the mutexes that protect the resources.
 */

#ifndef TERMINA__MUTEX_H__
#define TERMINA__MUTEX_H__

#include <termina/types.h>
#include <termina/task.h>

/**
 * @brief Variants of the mutex locking protocol.
 */
typedef enum {

    MutexProtocol__Ceiling

} termina__enum__MutexProtocol_t;

/**
 * @brief Parameters of the `Ceiling` variant: the ceiling priority.
 */
typedef struct {

    termina__task_prio_t _0;

} termina__enum__MutexProtocol__Ceiling_params_t;

/**
 * @brief Mutex locking protocol.
 */
typedef struct {

    termina__enum__MutexProtocol_t _variant;
    termina__enum__MutexProtocol__Ceiling_params_t Ceiling;

} MutexProtocol;

/**
 * @brief Initializes a mutex.
 *
 * @param[in]  mutex_id  Identifier of the mutex.
 * @param[in]  protocol  Locking protocol.
 * @param[out] status    Status of the operation: `termina__error__none`, or
 *                       `termina__error__mutex_init` if the identifier is
 *                       out of range or the mutex cannot be created.
 */
void termina__mutex__init(const termina__id_t mutex_id,
                           const MutexProtocol protocol,
                           termina__error_code_t * const status);

/**
 * @brief Locks a mutex.
 * 
 * If the mutex is already locked, the calling task blocks until it is
 * unlocked. Only tasks can call this function.
 * 
 * @param[in]   mutex_id  Identifier of the mutex.
 * @param[out]  status    Status of the operation: `termina__error__none`,
 *                        `termina__error__invalid_id`, or the error code that
 *                        the back-end returns.
 */
void termina__mutex__lock(const termina__id_t mutex_id,
                           termina__error_code_t * const status);

/**
 * @brief Unlocks a mutex.
 * 
 * The mutex must have been locked by the same task. Only tasks can call this
 * function.
 * 
 * @param[in]  mutex_id  Identifier of the mutex.
 * @param[out] status    Status of the operation: `termina__error__none`,
 *                       `termina__error__invalid_id`, or the error code that
 *                       the back-end returns.
 */
void termina__mutex__unlock(const termina__id_t mutex_id,
                             termina__error_code_t * const status);

#endif // TERMINA__MUTEX_H__
