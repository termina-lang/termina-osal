/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Table of the periodic timers and their creation by the back-end.
 */

#ifndef TERMINA__SHARED__PERIODIC_TIMER_H__
#define TERMINA__SHARED__PERIODIC_TIMER_H__

#include "config.h"

#include <termina.h>

#include <stdbool.h>

/**
 * @brief Periodic timer.
 */
typedef struct {

    //! Identifier of the event emitter.
    termina__id_t emitter_id;

    //! Identifier of the timer.
    termina__id_t timer_id;

    //! Connection of the timer to its task or handler.
    termina__periodic_timer_connection_t connection;

    //! Period of the timer.
    TimeVal period;

} termina__shared__periodic_timer_t;

#ifndef TERMINA__APP_CONFIG__PERIODIC_TIMERS
#error "config.h must define TERMINA__APP_CONFIG__PERIODIC_TIMERS"
#else
#if (TERMINA__APP_CONFIG__PERIODIC_TIMERS > 0)

/**
 * @brief Size of the timer object tables.
 */
#define TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE TERMINA__APP_CONFIG__PERIODIC_TIMERS

/**
 * @brief Checks whether a timer identifier is valid.
 *
 * @param[in] timer_id  Identifier of the timer.
 *
 * @return True if the identifier is less than the number of periodic timers
 *         of the application, false otherwise.
 */
static inline bool termina__shared__timer__is_valid_id(const termina__id_t timer_id) {
    return (timer_id < TERMINA__APP_CONFIG__PERIODIC_TIMERS);
}

#else

// The application defines no periodic timers. ISO C does not allow arrays of
// size zero, so the tables keep one unused element, and no identifier is valid.
#define TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE 1U

static inline bool termina__shared__timer__is_valid_id(const termina__id_t timer_id) {
    (void)timer_id;
    return false;
}

#endif
#endif

/**
 * @brief Table of the periodic timers, indexed by identifier.
 */
extern termina__shared__periodic_timer_t termina__shared__periodic_timer_object_table[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

/**
 * @brief Gets the timer object of an identifier, which must be valid.
 *
 * @param[in] timer_id  Identifier of the timer.
 *
 * @return Pointer to the timer object.
 */
static inline termina__shared__periodic_timer_t * termina__shared__timer__get_timer(const termina__id_t timer_id) {
    return &termina__shared__periodic_timer_object_table[timer_id];
}

/**
 * @brief Creates a periodic timer in the operating system.
 * 
 * Each operating system implements this function.
 *
 * @param[in]   timer_id  Identifier of the timer.
 * @param[out]  status    Status of the operation: `termina__error__none`, or
 *                        the error code of the back-end.
 */
void termina__periodic_timer_os__init(const termina__id_t timer_id,
                                       termina__error_code_t * const status);


#endif // TERMINA__SHARED__PERIODIC_TIMER_H__
