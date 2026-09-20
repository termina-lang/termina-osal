
#include <termina.h>


#include <termina/shared/list/list.h>
#include <termina/shared/task.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define TERMINA__POSIX__ID_IDLE_TASK TERMINA__ID__INVALID
#define TERMINA__POSIX__IDLE_TASK_STACK_SIZE 4096

/**
 * \brief The current task id.
 */
termina__id_t termina__posix__current_task_id;

pthread_t termina__posix__main_task_pthread;

termina__posix__task_t termina__posix__app_task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

_Bool termina__posix__task__disable_scheduling;

/**
 * \brief The ready task lists.
 * 
 * We have a list for each priority level. Each list is a FIFO list.
 * We do not have a list for the highest priority, since only the main task can 
 * be in that list.
 */
static termina__shared__list_t posix_ready_task_lists[TERMINA__TASK__NUMBER_OF_PRIORITIES];

termina__posix__task_t termina__posix__idle_task;

static void * termina__posix__task__idle_task_entry(void * const arg) {

    (void)arg;

    termina__posix__task__suspend(&termina__posix__idle_task);

    termina__posix__blocking_nesting_level = 1;

    termina__posix__signal__enable();

    for (;;) {
        usleep(1500);
    }

    return NULL;

}

static void termina__posix__task__create_idle_task(int32_t * const status) {

    (void)status;

    termina__posix__idle_task.current_priority = TERMINA__TASK__MINIMUM_PRIORITY;

    pthread_mutex_init(&termina__posix__idle_task.resume_mutex, NULL);
    pthread_cond_init(&termina__posix__idle_task.resume_cond, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, TERMINA__POSIX__IDLE_TASK_STACK_SIZE);

    pthread_create(&termina__posix__idle_task.pthread, &attr, termina__posix__task__idle_task_entry, NULL);

    return;

}


/**
 * \brief Suspends the execution of the current task.
 */
void termina__posix__task__suspend(termina__posix__task_t * const current_task) {

    pthread_mutex_lock(&current_task->resume_mutex);

    while (current_task->resume_task == 0) {
        pthread_cond_wait(&current_task->resume_cond, &current_task->resume_mutex);
    }

    current_task->resume_task = 0;

    pthread_mutex_unlock(&current_task->resume_mutex);

    return;

}


static void termina__posix__task__resume(termina__posix__task_t * const posix_task) {

    pthread_mutex_lock(&posix_task->resume_mutex);

    posix_task->resume_task = 1;

    pthread_cond_signal(&posix_task->resume_cond);

    pthread_mutex_unlock(&posix_task->resume_mutex);

    return;

}


static void * termina__posix__task__entry(void * const arg) {

    termina__id_t * task_id = (termina__id_t *)arg;

    termina__posix__task_t * posix_task = termina__posix__task__get_task(*task_id);
    termina__shared__task_t * task = termina__shared__task__get_task(*task_id);

    termina__posix__task__suspend(posix_task);

    termina__posix__blocking_nesting_level = 1;

    termina__posix__signal__enable();

    // This function call shall never return
    task->entry(task->arg);

    return NULL;

}


void termina__posix__task__init_scheduler(int32_t * const status) {

    *status = 0;

    // Initialize the ready task lists
    for (size_t i = 0; 
         i < TERMINA__TASK__NUMBER_OF_PRIORITIES && 0 == *status; 
         i = i + 1) {

        termina__shared__list__init(&posix_ready_task_lists[i], TERMINA__SHARED_LIST__FIFO, status);

    }

    termina__posix__task__disable_scheduling = 0;
    termina__posix__current_task_id = TERMINA__ID__INVALID;

    termina__posix__task__create_idle_task(status);

    return;

}

static termina__id_t termina__posix__task__select_next_task(void) {

    termina__posix__signal__disable();

    termina__id_t task_id = TERMINA__POSIX__ID_IDLE_TASK;

    for (size_t i = 0; i < TERMINA__TASK__NUMBER_OF_PRIORITIES; i = i + 1) {

        termina__id_t next_id = termina__shared__list__extract(&posix_ready_task_lists[i]);

        if (next_id != TERMINA__ID__INVALID) {
            task_id = next_id;
            break;
        }

    }

    termina__posix__signal__enable();

    return task_id;

}

static void termina__posix__task__switch_to(const termina__id_t next_task_id) {

    termina__posix__signal__disable();

    termina__posix__task_t * next_posix_task = termina__posix__task__get_task(next_task_id);
    termina__posix__task_t * current_posix_task = termina__posix__task__get_task(termina__posix__current_task_id);

    termina__posix__current_task_id = next_task_id;

    uint32_t local_block_nesting = termina__posix__blocking_nesting_level;

    termina__posix__task__resume(next_posix_task);

    termina__posix__task__suspend(current_posix_task);

    termina__posix__blocking_nesting_level = local_block_nesting;

    termina__posix__signal__enable();

    return;

}

void termina__posix__task__start_scheduler(void) {

    sigset_t main_signal_set;
    int input_signal;

    // Initialize the main task
    termina__posix__main_task_pthread = pthread_self();

    sigemptyset(&main_signal_set);
    sigaddset(&main_signal_set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &main_signal_set, NULL );

    termina__id_t next_task_id = termina__posix__task__select_next_task();
    termina__posix__task_t * next_posix_task = termina__posix__task__get_task(next_task_id);

    termina__posix__current_task_id = next_task_id;

    termina__posix__task__resume(next_posix_task);

    // Wait for the reboot signal
    sigwait(&main_signal_set, &input_signal);

    return;

}

void termina__os__task__init(const termina__id_t task_id,
                             int32_t * const status) {

    termina__posix__task_t * posix_task = termina__posix__task__get_task(task_id);
    termina__shared__task_t * task = termina__shared__task__get_task(task_id);

    posix_task->current_priority = task->priority;

    pthread_mutex_init(&posix_task->resume_mutex, NULL);
    pthread_cond_init(&posix_task->resume_cond, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setstacksize(&attr, task->stack_size);

    pthread_create(&posix_task->pthread, &attr, termina__posix__task__entry, &task->task_id);

    // Insert the task in the ready list
    termina__posix__task__insert_ready(task_id, posix_task->current_priority, status);

} 

void termina__posix__task__yield(void) {

    termina__posix__signal__disable();

    termina__id_t next_task = termina__posix__task__select_next_task();

    // Switch to the next task
    termina__posix__task__switch_to(next_task);

    termina__posix__signal__enable();

    return;

}

void termina__posix__task__schedule(void) {

    int32_t status = 0;
    
    termina__posix__signal__disable();

    // Get the structure of the current task
    termina__task_prio_t current_task_prio = termina__posix__task__get_current_priority(termina__posix__current_task_id);

    // Insert the current task in the ready list
    termina__posix__task__insert_ready(termina__posix__current_task_id, current_task_prio, &status);
    // TODO: Check the return status

    // Execute scheduler to check if a context switch is needed
    termina__id_t next_task_id = termina__posix__task__select_next_task();

    // If the next task is different from the current one, switch to the next task
    if (next_task_id != termina__posix__current_task_id) {
        termina__posix__task__switch_to(next_task_id);
    }

    termina__posix__signal__enable();

    return;
}

void termina__posix__task__insert_ready(const termina__id_t task_id, 
                                const termina__task_prio_t priority,
                                int32_t * const status) {


    if (task_id != TERMINA__POSIX__ID_IDLE_TASK) {
        termina__shared__list__append(&posix_ready_task_lists[priority], task_id, status);
    }

}
