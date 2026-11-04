#ifndef TERMINA__LOCK_H__
#define TERMINA__LOCK_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/task.h>
#include <termina/prelude.h>

/**
 * \brief Locks a resource.
 *
 * This function is used to lock a resource. The resource can be a mutex, a task
 * interrupt lock, or a handler interrupt lock. The function will be called at
 * the entry of a resource procedure.
 */
void termina__resource__lock(const termina__active_entity_t * const owner,
                             const termina__resource_lock_type_t * const lock_type);

/**
 * \brief Unlocks a resource.
 *
 * This function is used to unlock a resource. The resource can be a mutex, a task
 * interrupt lock, or a handler interrupt lock. The function will be called at
 * the exit of a resource procedure.
 *
 * @param[in] lock_type    the type of lock that was used to lock the resource.
 */
void termina__resource__unlock(const termina__active_entity_t * const owner,
                               const termina__resource_lock_type_t * const lock_type);

#endif // TERMINA__LOCK_H__
