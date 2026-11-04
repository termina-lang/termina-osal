#ifndef TERMINA__SHARED__LOCK_H__
#define TERMINA__SHARED__LOCK_H__

#include "config.h"

#include <termina.h>

#ifndef TERMINA__APP_CONFIG__IRQ_LOCKS
#error "config.h must define TERMINA__APP_CONFIG__IRQ_LOCKS"
#else
#if (TERMINA__APP_CONFIG__IRQ_LOCKS > 0)

/**
 * \brief Size of the interrupt lock tables.
 */
#define TERMINA__SHARED__IRQ_LOCK_TABLE_SIZE TERMINA__APP_CONFIG__IRQ_LOCKS

#else

// The application defines no interrupt locks. ISO C does not allow arrays of
// size zero, so the tables keep one unused element.
#define TERMINA__SHARED__IRQ_LOCK_TABLE_SIZE 1U

#endif
#endif

/**
 * \brief Takes an interrupt lock. This function is used to protect shared
 *        resources from concurrent access by tasks and event handlers.
 *
 * The back-end keeps what it needs to release the lock in the entry of the
 * lock: only its holder writes it, since the same lock is never taken twice.
 *
 * @param[in] lock_id the identifier of the interrupt lock of the resource.
 */
void termina__os__irq_lock(const termina__id_t lock_id);

/**
 * \brief Releases an interrupt lock taken with termina__os__irq_lock.
 *
 * @param[in] lock_id the identifier of the interrupt lock of the resource.
 */
void termina__os__irq_unlock(const termina__id_t lock_id);


#endif // TERMINA__SHARED__LOCK_H__
