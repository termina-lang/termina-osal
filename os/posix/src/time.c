
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Time services of the POSIX emulation: tick, uptime, delays and
 *        expiry of the timers.
 */

#include "config.h"

#include <termina.h>

#include <termina/shared/list/list.h>
#include <termina/shared/time.h>
#include <termina/shared/periodic_timer.h>
#include <termina/os/posix/time.h>
#include <termina/os/posix/periodic_timer.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>
#include <unistd.h>


uint64_t ticks = 0;

static pthread_t tick_task;

termina__shared__list_t termina__posix__delayed_tasks_list;

static void termina__posix__time__ticks_to_timeval(const uint64_t tick_count, TimeVal * const time) {

    uint64_t ticks_per_sec = termina__shared__time__ticks_per_sec();

    time->tv_sec = (uint32_t)(tick_count / ticks_per_sec);
    time->tv_usec = (uint32_t)((tick_count % ticks_per_sec) * TERMINA__TIME__MICROSECONDS_PER_TICK);

}

void termina__posix__time__get_current_time(TimeVal * const current_time) {

    termina__posix__time__ticks_to_timeval(ticks, current_time);

}

void termina__os__time__clock_get_uptime(TimeVal * const uptime) {

    termina__posix__time__get_current_time(uptime);

    return;

}

void termina__os__time__delay_in(const TimeVal * const time_val) {

    termina__error_code_t status = termina__error__none;

    TimeVal current_time = {0, 0};
    termina__posix__time__get_current_time(&current_time);

    termina__shared__add_timeval(&current_time, time_val);

    termina__shared__list__time_add(&termina__posix__delayed_tasks_list,
                                    termina__posix__current_task_id, &current_time, &status);

    if (termina__error__none == status) {

        if (0 == termina__posix__task__disable_scheduling) {
            termina__posix__task__yield();
        }

    }

    return;

}

static void * termina__posix__time__tick_task(void * arg) {

    (void)arg;

    for (;;) {

        // Gets the task object of the current task.
        termina__posix__task_t * current_task = termina__posix__task__get_task(termina__posix__current_task_id);
        // Sends SIGALRM to the thread of the current task, which runs the
        // tick handler.
        pthread_kill(current_task->pthread, SIGALRM);
        // Waits for one tick period.
        usleep(TERMINA__TIME__MICROSECONDS_PER_TICK);

    }

    return NULL;

}

/**
 * @brief Advances the current time by one tick and serves the timers that
 *        have expired.
 *
 * The function also inserts in the ready lists the tasks whose delay has
 * expired.
 * 
 * The tick handler calls this function.
 */
static void termina__posix__time__tick(void) {

    TimeVal current_time = {0, 0};

    termina__error_code_t status = termina__error__none;

    // Increments the tick counter.
    ticks = ticks + 1;

    // Converts the tick counter to a time value.
    termina__posix__time__get_current_time(&current_time);

    // Extracts the first expired timer.
    termina__id_t expired = termina__shared__list__extract_time(&termina__posix__timers_list, &current_time);

    while (expired != TERMINA__ID__INVALID) {

        termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(expired);
        termina__posix__periodic_timer_t * posix_timer = termina__posix__timer__get_timer(expired);

        // The action receives the time the timer was due, and the next one is
        // due a period after it.
        TimeVal scheduled_time = posix_timer->next_time;
        termina__shared__add_timeval(&posix_timer->next_time, &timer->period);
        termina__shared__list__time_add(&termina__posix__timers_list, expired, &posix_timer->next_time, &status);

        if (termina__error__none != status) {

            termina__except__runtime_failure(0U, termina__runtime_operation__timer_arm,
                                             termina__error__timer_arm);

        }

        posix_timer->handler(timer, &scheduled_time);

        expired = termina__shared__list__extract_time(&termina__posix__timers_list, &current_time);

    }

    expired = termina__shared__list__extract_time(&termina__posix__delayed_tasks_list, &current_time);

    while (expired != TERMINA__ID__INVALID) {

        termina__posix__task_t * posix_task = termina__posix__task__get_task(expired);

        termina__posix__task__insert_ready(expired, posix_task->current_priority, &status);

        if (termina__error__none != status) {

            termina__except__runtime_failure(0U, termina__runtime_operation__task_ready,
                                             termina__error__task_ready);

        }

        expired = termina__shared__list__extract_time(&termina__posix__delayed_tasks_list, &current_time);

    }

    return;

}


void termina__posix__time__tick_handler(int signum) {

    (void)signum;

    // Increments the blocking nesting level, since the handler runs with the
    // signals blocked.
    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level + 1;

    // Disables the scheduling while the tick is served.
    termina__posix__task__disable_scheduling = 1;

    // Serves the tick.
    termina__posix__time__tick();

    termina__posix__task__disable_scheduling = 0;

    termina__posix__task__schedule();

    // Decrements the blocking nesting level on leaving the handler.
    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level - 1;

}

void termina__posix__time__init(void) {

    termina__error_code_t status = termina__error__none;

    ticks = 0;

    // Initializes the list of timers.
    termina__shared__list__init(&termina__posix__timers_list, TERMINA__SHARED_LIST__TIME, &status);

    // Initializes the list of delayed tasks.
    termina__shared__list__init(&termina__posix__delayed_tasks_list, TERMINA__SHARED_LIST__TIME, &status);

    // Creates the tick thread.
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tick_task, &attr, termina__posix__time__tick_task, NULL);

}
