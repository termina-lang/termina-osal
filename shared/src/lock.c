
#include <termina.h>
#include <termina/shared/lock.h>
#include <termina/shared/mutex.h>

termina__lock_t termina__resource__lock(const termina__active_entity_t * const owner,
                                          termina__resource_lock_type_t * const lock_type) {

    (void)owner;

    termina__lock_t lock = 0;

    if (lock_type->type == termina__resource_lock_type__mutex) {

        int32_t status = 0;

        // Lock a mutex-protected resource
        termina__os_mutex__lock(lock_type->mutex.mutex_id, &status);

        // TODO: Check if the lock was successful

    } else if (lock_type->type == termina__resource_lock_type__irq) {

        lock = termina__os__irq_lock();

    } else {
        // Do nothing, no lock is needed
    }
    
    return lock;

}

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
                                termina__lock_t lock) {

    (void)owner;

    if (lock_type->type == termina__resource_lock_type__mutex) {

        // Unlock a mutex-protected resource
        int32_t status = 0;
        termina__os_mutex__unlock(lock_type->mutex.mutex_id, &status);
        // TODO: Check if the unlock was successful

    } else if (lock_type->type == termina__resource_lock_type__irq) {

        termina__os__irq_unlock(lock);

    } else {
        // Do nothing, no lock is needed
    }

}