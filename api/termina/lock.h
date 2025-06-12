#ifndef __TERMINA__LOCK_H__
#define __TERMINA__LOCK_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/task.h>
#include <termina/prelude.h>

/**
 * \brief Type used to represent a temporary lock value.
 *
 * This type is returned by an nterrupt lock. For the type being, the type is made
 * operating-system-independent.
 */
typedef int32_t __termina_lock_t;

/**
 * \brief Locks a resource.
 * 
 * This function is used to lock a resource. The resource can be a mutex, a task
 * interrupt lock, or a handler interrupt lock. The function will be called at
 * the entry of a resource procedure.
 */
__termina_lock_t __termina_resource__lock(const __termina_active_entity_t * const owner,
                                          __termina_resource_lock_type_t * const lock_type);

/**
 * \brief Unlocks a resource.
 * 
 * This function is used to unlock a resource. The resource can be a mutex, a task
 * interrupt lock, or a handler interrupt lock. The function will be called at
 * the exit of a resource procedure.
 * 
 * @param[in] lock_type    the type of lock that was used to lock the resource.
 */
void __termina_resource__unlock(const __termina_active_entity_t * const owner,
                                __termina_resource_lock_type_t * const lock_type,
                                __termina_lock_t lock);

#endif // __TERMINA__LOCK_H___
