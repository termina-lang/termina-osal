#ifndef __TERMINA__SHARED__PERIODIC_TIMER_H__
#define __TERMINA__SHARED__PERIODIC_TIMER_H__

#include <termina.h>

#include <stdbool.h>

typedef struct {

    // \brief Identifier of the event emitter
    __termina_id_t emitter_id;

    // \brief Identifier of the timer
    __termina_id_t timer_id;

    //! Source port of the timer event 
    __termina_periodic_timer_connection_t connection;

    //! Period of the timer
    TimeVal period;

} __termina_shared_periodic_timer_t;

#ifndef __TERMINA_APP_CONFIG_PERIODIC_TIMERS
#error "config.h must define __TERMINA_APP_CONFIG_PERIODIC_TIMERS"
#else
#if (__TERMINA_APP_CONFIG_PERIODIC_TIMERS > 0)

/**
 * \brief Size of the timer object tables.
 */
#define __TERMINA_SHARED_PERIODIC_TIMER_TABLE_SIZE __TERMINA_APP_CONFIG_PERIODIC_TIMERS

/**
 * \brief Checks whether a timer identifier is valid.
 *
 * @param[in] timer_id the identifier of the timer.
 *
 * @return true if the identifier is less than the number of periodic timers
 *         defined in the application, false otherwise.
 */
static inline bool __termina_shared_timer__is_valid_id(const __termina_id_t timer_id) {
    return (timer_id < __TERMINA_APP_CONFIG_PERIODIC_TIMERS);
}

#else

// The application defines no periodic timers. ISO C does not allow arrays of
// size zero, so the tables keep one unused element, and no identifier is valid.
#define __TERMINA_SHARED_PERIODIC_TIMER_TABLE_SIZE 1U

static inline bool __termina_shared_timer__is_valid_id(const __termina_id_t timer_id) {
    (void)timer_id;
    return false;
}

#endif
#endif

/**
 * \brief Array of timer objects.
 */
extern __termina_shared_periodic_timer_t __termina_shared_timers[__TERMINA_SHARED_PERIODIC_TIMER_TABLE_SIZE];

static inline __termina_shared_periodic_timer_t * __termina_shared_timer__get_timer(const __termina_id_t timer_id) {
    return &__termina_shared_timers[timer_id];
}

/**
 * \brief Creates a periodic timer.
 *        Operating system implementation-dependent function.
 * 
 * @param[in]   timer_id  the identifier of the timer.
 * @param[out]  status    Zero if the timer was created correctly or
 *                        a different value in case of error.
 */
void __termina_periodic_timer_os__init(const __termina_id_t timer_id,
                                       int32_t * const status);


#endif // __TERMINA__SHARED__PERIODIC_TIMER_H__
