/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Table of the mutexes and the mutex operations that each operating
 *        system implements.
 */

#ifndef TERMINA__SHARED__MUTEX_H__
#define TERMINA__SHARED__MUTEX_H__

#include "config.h"

#include <termina.h>

#include <stdbool.h>

/**
 * @brief Initialization data of a mutex.
 *
 * The structure stores the mutex data that the architecture of the
 * application defines and that is known at compile time. The transpiler
 * generates a read-only structure with this data for each mutex of the
 * application.
 */
typedef struct {

    //! Mutex identifier.
    termina__id_t mutex_id;

    //! Mutex locking protocol.
    MutexProtocol protocol;

} termina__shared__mutex_t;

#ifndef TERMINA__APP_CONFIG__MUTEXES
#error "config.h must define TERMINA__APP_CONFIG__MUTEXES"
#else
#if (TERMINA__APP_CONFIG__MUTEXES > 0)

/**
 * @brief Size of the mutex object tables.
 */
#define TERMINA__SHARED__MUTEX_TABLE_SIZE TERMINA__APP_CONFIG__MUTEXES

/**
 * @brief Checks whether a mutex identifier is valid.
 *
 * @param[in] mutex_id  Identifier of the mutex.
 *
 * @return True if the identifier is less than the number of mutexes of the
 *         application, false otherwise.
 */
static inline bool termina__shared__mutex__is_valid_id(const termina__id_t mutex_id) {
    return (mutex_id < TERMINA__APP_CONFIG__MUTEXES);
}

#else

// The application defines no mutexes. ISO C does not allow arrays of size zero,
// so the tables keep one unused element, and no identifier is valid.
#define TERMINA__SHARED__MUTEX_TABLE_SIZE 1U

static inline bool termina__shared__mutex__is_valid_id(const termina__id_t mutex_id) {
    (void)mutex_id;
    return false;
}

#endif
#endif

/** @brief Table of the mutexes, indexed by identifier. */
extern termina__shared__mutex_t termina__shared__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

/**
 * @brief Gets the mutex object of a mutex identifier.
 * 
 * The identifier must be valid, that is, less than the number of mutexes of
 * the application.
 * 
 * @param[in] mutex_id  Identifier of the mutex.
 * 
 * @return Pointer to the mutex object.
 */
static inline termina__shared__mutex_t * termina__shared__mutex__get_mutex(
    const termina__id_t mutex_id) {

    return &termina__shared__mutex_object_table[mutex_id];

}


/**
 * @brief Creates a mutex in the operating system.
 * 
 * The mutex is initialized with the owner set to `TERMINA__ID__INVALID` and
 * the list of waiting tasks empty.
 * 
 * @param[in]   mutex_id  Identifier of the mutex.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__mutex__init(const termina__id_t mutex_id,
                              termina__error_code_t * const status);

/**
 * @brief Locks a mutex.
 * 
 * If the mutex is already locked, the calling task blocks until it is
 * unlocked.
 * 
 * @param[in]   mutex_id  Identifier of the mutex.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__mutex__lock(const termina__id_t mutex_id,
                              termina__error_code_t * const status);

/**
 * @brief Unlocks a mutex.
 * 
 * If there are tasks waiting for the mutex, the one with the highest priority
 * is unblocked.
 * 
 * @param[in]   mutex_id  Identifier of the mutex.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                termina__error_code_t * const status);

#endif // TERMINA__SHARED__MUTEX_H__
