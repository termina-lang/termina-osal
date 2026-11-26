/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Locking of the resources at the entry and exit of their procedures.
 */

#ifndef TERMINA__LOCK_H__
#define TERMINA__LOCK_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/task.h>
#include <termina/prelude.h>

/**
 * @brief Locks a resource.
 *
 * The lock is a mutex, an interrupt lock or none, as `lock_type` indicates.
 * The generated code calls this function at the entry of a resource
 * procedure. If the mutex cannot be taken, the function raises
 * `ERuntimeFailure`.
 *
 * @param[in] owner      Active entity that calls the procedure.
 * @param[in] lock_type  Type of lock that protects the resource.
 */
void termina__resource__lock(const termina__active_entity_t * const owner,
                             const termina__resource_lock_type_t * const lock_type);

/**
 * @brief Unlocks a resource.
 *
 * The lock is a mutex, an interrupt lock or none, as `lock_type` indicates.
 * The generated code calls this function at the exit of a resource
 * procedure. If the mutex cannot be released, the function raises
 * `ERuntimeFailure`.
 *
 * @param[in] owner      Active entity that calls the procedure.
 * @param[in] lock_type  Type of lock that was used to lock the resource.
 */
void termina__resource__unlock(const termina__active_entity_t * const owner,
                               const termina__resource_lock_type_t * const lock_type);

#endif // TERMINA__LOCK_H__
