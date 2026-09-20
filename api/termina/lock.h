#ifndef TERMINA__LOCK_H__
#define TERMINA__LOCK_H__

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
typedef uint32_t termina__lock_t;

/**
 * \brief Locks a resource.
 * 
 * This function is used to lock a resource. The resource can be a mutex, a task
 * interrupt lock, or a handler interrupt lock. The function will be called at
 * the entry of a resource procedure.
 */
termina__lock_t termina__resource__lock(const termina__active_entity_t * const owner,
                                          termina__resource_lock_type_t * const lock_type);

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
                                termina__resource_lock_type_t * const lock_type,
                                termina__lock_t lock);

#endif // TERMINA__LOCK_H__
