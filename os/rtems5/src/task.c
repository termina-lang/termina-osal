
#include <termina.h>

#include <termina/shared/task.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_task_id;

} __rtems_task_t;

__rtems_task_t __rtems_task_object_table[__TERMINA_APP_CONFIG_TASKS];

static inline __rtems_task_t * __rtems_task__get_task(const __termina_id_t task_id) {
    return &__rtems_task_object_table[task_id];
}

/**
 * \brief Array used to generate the names of the tasks that are
 *        created.
 */
static int8_t ntask_name[5]  = "0000";

static rtems_task __rtems_task__entry (rtems_task_argument arg) {

    __termina_id_t * task_id = (__termina_id_t *)arg;

    __termina_shared_task_t * task = __termina_shared_task__get_task(*task_id);

    // This function call shall never return
    task->entry(task->arg);

    return;

}

void __termina_os_task__init(const __termina_id_t task_id,
                             Status * const status) {

    status->__variant = Status__Success;

    __termina_shared_task_t * task = __termina_shared_task__get_task(task_id);
    __rtems_task_t * rtems_task = __rtems_task__get_task(task_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);
    name = rtems_build_name(ntask_name[0], ntask_name[1], ntask_name[2],
                            ntask_name[3]);

    if (rtems_task_create(name, task->priority, task->stack_size, 
                          RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES,
                          &rtems_task->rtems_task_id) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    if (Status__Success == status->__variant) {

        if (rtems_task_start(rtems_task->rtems_task_id, 
                             __rtems_task__entry, 
                             (rtems_task_argument)&task->task_id) != RTEMS_SUCCESSFUL) {

            status->__variant = Status__Error;
            status->Error.__0.__variant = Exception__InternalError;

        }

    }

    return;
}
