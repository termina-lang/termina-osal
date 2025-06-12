
#include <termina.h>
#include <termina/shared/lock.h>
#include <termina/shared/mutex.h>

__termina_lock_t __termina_resource__lock(const __termina_active_entity_t * const owner,
                                          __termina_resource_lock_type_t * const lock_type) {

    __termina_lock_t lock = 0;

    if (lock_type->type == __termina_resource_lock_type__mutex) {

        int32_t status = 0;

        // Lock a mutex-protected resource
        __termina_os_mutex__lock(lock_type->mutex.mutex_id, &status);

        // TODO: Check if the lock was successful

    } else if (lock_type->type == __termina_resource_lock_type__irq) {

        if (owner->type == __termina_active_entity__task) {
            // Lock interrupts from a task
            lock = __termina_os_task__irq_lock();
        } else {
            // Lock interrupts from a handler
            lock = __termina_os_handler__irq_lock();
        } 

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
void __termina_resource__unlock(const __termina_active_entity_t * const owner,
                                __termina_resource_lock_type_t * const lock_type,
                                __termina_lock_t lock) {

    if (lock_type->type == __termina_resource_lock_type__mutex) {

        // Unlock a mutex-protected resource
        int32_t status = 0;
        __termina_os_mutex__unlock(lock_type->mutex.mutex_id, &status);
        // TODO: Check if the unlock was successful

    } else if (lock_type->type == __termina_resource_lock_type__irq) {

        if (owner->type == __termina_active_entity__task) {
            // Unlock interrupts from a task
            __termina_os_task__irq_unlock(lock);
        } else {
            // Unlock interrupts from a handler
            __termina_os_handler__irq_unlock(lock);
        }

    } else {
        // Do nothing, no lock is needed
    }

}