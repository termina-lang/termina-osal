
/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Locking of the resources at the entry and exit of their procedures.
 */

#include <termina.h>
#include <termina/shared/lock.h>
#include <termina/shared/mutex.h>

void termina__resource__lock(const termina__active_entity_t * const owner,
                             const termina__resource_lock_type_t * const lock_type) {

    (void)owner;

    if (lock_type->type == termina__resource_lock_type__mutex) {

        termina__error_code_t status = termina__error__none;

        // Lock a mutex-protected resource
        termina__os__mutex__lock(lock_type->mutex.mutex_id, &status);

        if (termina__error__none != status) {

            termina__except__runtime_failure((uintptr_t)__builtin_return_address(0),
                                             termina__runtime_operation__mutex_lock,
                                             status);

        }

    } else if (lock_type->type == termina__resource_lock_type__irq) {

        termina__os__irq_lock(lock_type->irq.lock_id);

    } else {
        // Do nothing, no lock is needed
    }

}

void termina__resource__unlock(const termina__active_entity_t * const owner,
                               const termina__resource_lock_type_t * const lock_type) {

    (void)owner;

    if (lock_type->type == termina__resource_lock_type__mutex) {

        // Unlock a mutex-protected resource
        termina__error_code_t status = termina__error__none;
        termina__os__mutex__unlock(lock_type->mutex.mutex_id, &status);

        if (termina__error__none != status) {

            termina__except__runtime_failure((uintptr_t)__builtin_return_address(0),
                                             termina__runtime_operation__mutex_unlock,
                                             status);

        }

    } else if (lock_type->type == termina__resource_lock_type__irq) {

        termina__os__irq_unlock(lock_type->irq.lock_id);

    } else {
        // Do nothing, no lock is needed
    }

}