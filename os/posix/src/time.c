
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

    uint64_t ticks_per_sec = termina__posix__time__ticks_per_sec();

    time->tv_sec = (uint32_t)(tick_count / ticks_per_sec);
    time->tv_usec = (uint32_t)((tick_count % ticks_per_sec) * TERMINA__TIME__MICROSECONDS_PER_TICK);

}

void termina__posix__time__get_current_time(TimeVal * const current_time) {

    termina__posix__time__ticks_to_timeval(ticks, current_time);

}

static void * termina__posix__time__tick_task(void * arg) {

    (void)arg;

    for (;;) {

        // Get the POSIX internal structure of the current task
        termina__posix__task_t * current_task = termina__posix__task__get_task(termina__posix__current_task_id);
        // Send the tick signal to the current task. This will trigger
        // the tick handler
        pthread_kill(current_task->pthread, SIGALRM);
        // Wait for the next tick
        usleep(TERMINA__TIME__MICROSECONDS_PER_TICK);

    }

    return NULL;

}

/**
 * \brief Tick function.
 * 
 * This function is called by the tick handler to update the current time and
 * trigger the execution of the programmed timers that have expired.
 */
static void termina__posix__time__tick(void) {

    TimeVal current_time = {0, 0};

    int32_t status = 0;

    // Increment the tick counter
    ticks = ticks + 1;

    // Get current time in timeval format
    termina__posix__time__get_current_time(&current_time);

    // Extract the expired timers
    termina__id_t expired = termina__shared__list__extract_time(&termina__posix__timers_list, &current_time);

    while (expired != TERMINA__ID__INVALID) {

        termina__shared__periodic_timer_t * timer = termina__shared__timer__get_timer(expired);
        termina__posix__periodic_timer_t * posix_timer = termina__posix__timer__get_timer(expired);

        // Auto-reload the timer
        TimeVal next_abs_time = current_time;
        termina__shared__add_timeval(&next_abs_time, &timer->period);
        termina__shared__list__time_add(&termina__posix__timers_list, expired, &next_abs_time, &status);
        // TODO: Check the status value returned by the function

        posix_timer->handler(timer, &current_time);

        expired = termina__shared__list__extract_time(&termina__posix__timers_list, &current_time);

    }

    expired = termina__shared__list__extract_time(&termina__posix__delayed_tasks_list, &current_time);

    while (expired != TERMINA__ID__INVALID) {

        termina__posix__task_t * posix_task = termina__posix__task__get_task(expired);

        termina__posix__task__insert_ready(expired, posix_task->current_priority, &status);

        expired = termina__shared__list__extract_time(&termina__posix__delayed_tasks_list, &current_time);

    }

    return;

}


void termina__posix__time__tick_handler(int signum) {

    (void)signum;

    // Increment the blocking nesting level to indicate that the tick handler is
    // running with the signals disabled
    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level + 1;

    // Disable the scheduling to avoid context switches when executing
    // the tick
    termina__posix__task__disable_scheduling = 1;

    // Trigger the tick computation
    termina__posix__time__tick();

    termina__posix__task__disable_scheduling = 0;

    termina__posix__task__schedule();

    // Decrement the blocking nesting level to indicate that we are leaving the
    // critical section of the tick handler
    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level - 1;

}

void termina__posix__time__init(void) {

    int32_t status = 0;

    ticks = 0;

    // Initialize the list of timers
    termina__shared__list__init(&termina__posix__timers_list, TERMINA__SHARED_LIST__TIME, &status);

    // Initialize the list of delayed tasks
    termina__shared__list__init(&termina__posix__delayed_tasks_list, TERMINA__SHARED_LIST__TIME, &status);

    // Create the tick task
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tick_task, &attr, termina__posix__time__tick_task, NULL);

}
