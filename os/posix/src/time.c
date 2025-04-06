
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

__termina_shared_list_t __posix_delayed_tasks_list;

static void __posix_time__ticks_to_timeval(const uint64_t ticks, TimeVal * const time) {

    uint64_t ticks_per_sec = __posix_time__ticks_per_sec();

    time->tv_sec = ticks / ticks_per_sec;
    time->tv_usec = (ticks % ticks_per_sec) * __TERMINA_MICROSECONDS_PER_TICK;

}

void __posix_time__get_current_time(TimeVal * const current_time) {

    __posix_time__ticks_to_timeval(ticks, current_time);

}

static void * __posix_time__tick_task(void * arg) {

    for (;;) {

        // Get the POSIX internal structure of the current task
        __posix_task_t * current_task = __posix_task__get_task(__posix_current_task_id);
        // Send the tick signal to the current task. This will trigger
        // the tick handler
        pthread_kill(current_task->pthread, SIGALRM);
        // Wait for the next tick
        usleep(__TERMINA_MICROSECONDS_PER_TICK);

    }

    return NULL;

}

/**
 * \brief Tick function.
 * 
 * This function is called by the tick handler to update the current time and
 * trigger the execution of the programmed timers that have expired.
 */
void __posix_time__tick(void) {

    TimeVal current_time = {0, 0};

    Status status;
    status.__variant = Status__Success;

    // Increment the tick counter
    ticks = ticks + 1;

    // Get current time in timeval format
    __posix_time__get_current_time(&current_time);

    // Extract the expired timers
    __termina_id_t expired = __termina_shared_list__extract_time(&__posix_timers_list, &current_time);

    while (expired != __TERMINA_ID_INVALID) {

        __termina_shared_periodic_timer_t * timer = __termina_shared_timer__get_timer(expired);
        __posix_periodic_timer_t * posix_timer = __posix_timer__get_timer(expired);

        // Auto-reload the timer
        TimeVal next_abs_time = current_time;
        __termina_shared__add_timeval(&next_abs_time, &timer->period);
        __termina_shared_list__time_add(&__posix_timers_list, expired, &next_abs_time, &status);
        // TODO: Check the status value returned by the function

        posix_timer->handler(&timer->connection, &current_time);

        expired = __termina_shared_list__extract_time(&__posix_timers_list, &current_time);

    }

    expired = __termina_shared_list__extract_time(&__posix_delayed_tasks_list, &current_time);

    while (expired != __TERMINA_ID_INVALID) {

        __posix_task_t * posix_task = __posix_task__get_task(expired);

        __posix_task__insert_ready(expired, posix_task->current_priority, &status);

        expired = __termina_shared_list__extract_time(&__posix_delayed_tasks_list, &current_time);

    }

    return;

}


void __posix_time__tick_handler(int signum) {

    // Increment the blocking nesting level to indicate that the tick handler is
    // running with the signals disabled
    __posix_blocking_nesting_level = __posix_blocking_nesting_level + 1;

    // Disable the scheduling to avoid context switches when executing
    // the tick
    __posix_task__disable_scheduling = 1;

    // Trigger the tick computation
    __posix_time__tick();

    __posix_task__disable_scheduling = 0;

    __posix_task__schedule();

    // Decrement the blocking nesting level to indicate that we are leaving the
    // critical section of the tick handler
    __posix_blocking_nesting_level = __posix_blocking_nesting_level - 1;

}

void __posix_time__init(void) {

    Status status;
    status.__variant = Status__Success;

    ticks = 0;

    // Initialize the list of timers
    __termina_shared_list__init(&__posix_timers_list, __TERMINA_SHARED_LIST__TIME, &status);

    // Initialize the list of delayed tasks
    __termina_shared_list__init(&__posix_delayed_tasks_list, __TERMINA_SHARED_LIST__TIME, &status);

    // Create the tick task
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tick_task, &attr, __posix_time__tick_task, NULL);

}
