#ifndef TERMINA__SHARED__PERIODIC_TIMER_H__
#define TERMINA__SHARED__PERIODIC_TIMER_H__

#include <termina.h>

#include <stdbool.h>

typedef struct {

    // \brief Identifier of the event emitter
    termina__id_t emitter_id;

    // \brief Identifier of the timer
    termina__id_t timer_id;

    //! Source port of the timer event 
    termina__periodic_timer_connection_t connection;

    //! Period of the timer
    TimeVal period;

} termina__shared_periodic_timer_t;

#ifndef TERMINA__APP_CONFIG__PERIODIC_TIMERS
#error "config.h must define TERMINA__APP_CONFIG__PERIODIC_TIMERS"
#else
#if (TERMINA__APP_CONFIG__PERIODIC_TIMERS > 0)

/**
 * \brief Size of the timer object tables.
 */
#define TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE TERMINA__APP_CONFIG__PERIODIC_TIMERS

/**
 * \brief Checks whether a timer identifier is valid.
 *
 * @param[in] timer_id the identifier of the timer.
 *
 * @return true if the identifier is less than the number of periodic timers
 *         defined in the application, false otherwise.
 */
static inline bool termina__shared_timer__is_valid_id(const termina__id_t timer_id) {
    return (timer_id < TERMINA__APP_CONFIG__PERIODIC_TIMERS);
}

#else

// The application defines no periodic timers. ISO C does not allow arrays of
// size zero, so the tables keep one unused element, and no identifier is valid.
#define TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE 1U

static inline bool termina__shared_timer__is_valid_id(const termina__id_t timer_id) {
    (void)timer_id;
    return false;
}

#endif
#endif

/**
 * \brief Array of timer objects.
 */
extern termina__shared_periodic_timer_t termina__shared_timers[TERMINA__SHARED__PERIODIC_TIMER_TABLE_SIZE];

static inline termina__shared_periodic_timer_t * termina__shared_timer__get_timer(const termina__id_t timer_id) {
    return &termina__shared_timers[timer_id];
}

/**
 * \brief Creates a periodic timer.
 *        Operating system implementation-dependent function.
 * 
 * @param[in]   timer_id  the identifier of the timer.
 * @param[out]  status    Zero if the timer was created correctly or
 *                        a different value in case of error.
 */
void termina__periodic_timer_os__init(const termina__id_t timer_id,
                                       int32_t * const status);


#endif // TERMINA__SHARED__PERIODIC_TIMER_H__
