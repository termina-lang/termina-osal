
#include <termina.h>


#include <termina/shared/list.h>
#include <termina/shared/task.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define __POSIX_ID_IDLE_TASK __TERMINA_ID_INVALID
#define __POSIX_IDLE_TASK_STACK_SIZE 4096

/**
 * \brief The current task id.
 */
__termina_id_t __posix_current_task_id;

pthread_t __posix_main_task_pthread;

__posix_task_t __posix_app_task_object_table[__TERMINA_APP_CONFIG_TASKS];

_Bool __posix_task__disable_scheduling;

/**
 * \brief The ready task lists.
 * 
 * We have a list for each priority level. Each list is a FIFO list.
 * We do not have a list for the highest priority, since only the main task can 
 * be in that list.
 */
static __termina_shared_list_t posix_ready_task_lists[__TERMINA_TASK_NUMBER_OF_PRIORITIES];

__posix_task_t __posix_idle_task;

static void * __posix_task__idle_task_entry(void * const arg) {

    __posix_task__suspend(&__posix_idle_task);

    __posix_blocking_nesting_level = 1;

    __posix_signal__enable();

    for (;;) {
        usleep(1500);
    }

    return NULL;

}

static void __posix_task__create_idle_task(Status * const status) {

    pthread_mutex_init(&__posix_idle_task.resume_mutex, NULL);
    pthread_cond_init(&__posix_idle_task.resume_cond, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, __POSIX_IDLE_TASK_STACK_SIZE);

    pthread_create(&__posix_idle_task.pthread, &attr, __posix_task__idle_task_entry, NULL);

    return;

}


/**
 * \brief Suspends the execution of the current task.
 */
void __posix_task__suspend(__posix_task_t * const current_task) {

    pthread_mutex_lock(&current_task->resume_mutex);

    while (current_task->resume_task == 0) {
        pthread_cond_wait(&current_task->resume_cond, &current_task->resume_mutex);
    }

    current_task->resume_task = 0;

    pthread_mutex_unlock(&current_task->resume_mutex);

    return;

}


void __posix_task__resume(__posix_task_t * const posix_task) {

    pthread_mutex_lock(&posix_task->resume_mutex);

    posix_task->resume_task = 1;

    pthread_cond_signal(&posix_task->resume_cond);

    pthread_mutex_unlock(&posix_task->resume_mutex);

    return;

}


static void * __posix_task__entry(void * const arg) {

    __termina_id_t * task_id = (__termina_id_t *)arg;

    __posix_task_t * posix_task = __posix_task__get_task(*task_id);
    __termina_shared_task_t * task = __termina_shared_task__get_task(*task_id);

    __posix_task__suspend(posix_task);

    __posix_blocking_nesting_level = 1;

    __posix_signal__enable();

    // This function call shall never return
    task->entry(task->arg);

    return NULL;

}


void __posix_task__init_scheduler(Status * const status) {

    status->__variant = Status__Success;

    // Initialize the ready task lists
    for (size_t i = 0; 
         i < __TERMINA_TASK_NUMBER_OF_PRIORITIES && Status__Success == status->__variant; 
         i = i + 1) {

        __termina_shared_list__init(&posix_ready_task_lists[i], __TERMINA_SHARED_LIST__FIFO, status);

    }

    __posix_task__disable_scheduling = 0;
    __posix_current_task_id = __TERMINA_ID_INVALID;

    __posix_task__create_idle_task(status);

    return;

}

static __termina_id_t __posix_task__select_next_task(void) {

    __posix_signal__disable();

    __termina_id_t task_id = __POSIX_ID_IDLE_TASK;

    for (size_t i = 0; i < __TERMINA_TASK_NUMBER_OF_PRIORITIES; i = i + 1) {

        __termina_id_t next_id = __termina_shared_list__extract(&posix_ready_task_lists[i]);

        if (next_id != __TERMINA_ID_INVALID) {
            task_id = next_id;
            break;
        }

    }

    __posix_signal__enable();

    return task_id;

}

static void __posix_task__switch_to(const __termina_id_t next_task_id) {

    __posix_signal__disable();

    __posix_task_t * next_posix_task = __posix_task__get_task(next_task_id);
    __posix_task_t * current_posix_task = __posix_task__get_task(__posix_current_task_id);

    __posix_current_task_id = next_task_id;

    uint32_t local_block_nesting = __posix_blocking_nesting_level;

    __posix_task__resume(next_posix_task);

    __posix_task__suspend(current_posix_task);

    __posix_blocking_nesting_level = local_block_nesting;

    __posix_signal__enable();

    return;

}

void __posix_task__start_scheduler(void) {

    sigset_t main_signal_set;
    int input_signal;

    // Initialize the main task
    __posix_main_task_pthread = pthread_self();

    sigemptyset(&main_signal_set);
    sigaddset(&main_signal_set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &main_signal_set, NULL );

    __termina_id_t next_task_id = __posix_task__select_next_task();
    __posix_task_t * next_posix_task = __posix_task__get_task(next_task_id);

    __posix_current_task_id = next_task_id;

    __posix_task__resume(next_posix_task);

    // Wait for the shutdown signal
    sigwait(&main_signal_set, &input_signal);

    return;

}

void __termina_os_task__init(const __termina_id_t task_id,
                             Status * const status) {

    __posix_task_t * posix_task = __posix_task__get_task(task_id);
    __termina_shared_task_t * task = __termina_shared_task__get_task(task_id);

    posix_task->current_priority = task->priority;

    pthread_mutex_init(&posix_task->resume_mutex, NULL);
    pthread_cond_init(&posix_task->resume_cond, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, task->stack_size);

    pthread_create(&posix_task->pthread, &attr, __posix_task__entry, &task->task_id);

    // Insert the task in the ready list
    __posix_task__insert_ready(task_id, posix_task->current_priority, status);

} 

void __posix_task__yield(void) {

    __posix_signal__disable();

    __termina_id_t next_task = __posix_task__select_next_task();

    // Switch to the next task
    __posix_task__switch_to(next_task);

    __posix_signal__enable();

    return;

}

void __posix_task__schedule(void) {

    Status status;
    status.__variant = Status__Success;
    
    __posix_signal__disable();

    // Get the structure of the current task
    __termina_task_prio_t current_task_prio = __posix_task__get_current_priority(__posix_current_task_id);

    // Insert the current task in the ready list
    __posix_task__insert_ready(__posix_current_task_id, current_task_prio, &status);
    // TODO: Check the return status

    // Execute scheduler to check if a context switch is needed
    __termina_id_t next_task_id = __posix_task__select_next_task();

    // If the next task is different from the current one, switch to the next task
    if (next_task_id != __posix_current_task_id) {
        __posix_task__switch_to(next_task_id);
    }

    __posix_signal__enable();

    return;
}

void __posix_task__insert_ready(const __termina_id_t task_id, 
                                const __termina_task_prio_t priority,
                                Status * const status) {


    __termina_shared_list__append(&posix_ready_task_lists[priority], task_id, status);

}
