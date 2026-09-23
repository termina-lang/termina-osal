#ifndef TERMINA__SHARED__MUTEX_H__
#define TERMINA__SHARED__MUTEX_H__

#include "config.h"

#include <termina.h>

#include <stdbool.h>

/**
 * \brief Termina mutex initialization data structure.
 *        This structure is used to store mutex data that is defined by the application
 *        architecture itself and known at compile time. The transpiler will generate a
 *        read-only structure with this data for each of the application mutexes.
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
 * \brief Size of the mutex object tables.
 */
#define TERMINA__SHARED__MUTEX_TABLE_SIZE TERMINA__APP_CONFIG__MUTEXES

/**
 * \brief Checks whether a mutex identifier is valid.
 *
 * @param[in] mutex_id the mutex identifier.
 *
 * @return true if the identifier is less than the number of mutexes defined in
 *         the application, false otherwise.
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

extern termina__shared__mutex_t termina__shared__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

/**
 * \brief Gets the mutex object from the mutex identifier.
 * 
 * This function returns the mutex object from the mutex id. It assumes that the
 * mutex id is valid, i.e., it is less than the number of mutexes defined in the
 * application.
 * 
 * @param[in] mutex_id the mutex identifier.
 * 
 * @return the mutex object.
 */
static inline termina__shared__mutex_t * termina__shared__mutex__get_mutex(
    const termina__id_t mutex_id) {

    return &termina__shared__mutex_object_table[mutex_id];

}


/**
 * \brief Initializes a mutex.
 * 
 * This function initializes a mutex. The mutex is initialized with the owner set to
 * TERMINA__ID__INVALID and the waiting tasks list empty.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was initialized successfully or another
 *                        value in case of an error.      
 */
void termina__os__mutex__init(const termina__id_t mutex_id,
                              int32_t * const status);

/**
 * \brief Locks a mutex.
 * 
 * This function locks a mutex. If the mutex is already locked, the task is blocked
 * until the mutex is unlocked.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was locked successfully or another value
 *                        in case of error.
 */
void termina__os__mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status);

/**
 * \brief Unlocks a mutex.
 * 
 * This function unlocks a mutex. If there are tasks waiting for the mutex, the task
 * with the highest priority is unblocked.
 * 
 * @param[in]   mutex_id  the mutex identifier.
 * @param[out]  status    Zero if the mutex was unlocked successfully or another value
 *                        in case of error.
 */
void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status);

#endif // TERMINA__SHARED__MUTEX_H__
