
#include <termina.h>

#include <termina/shared/task.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_task_id;

} termina__rtems__task_t;

termina__rtems__task_t termina__rtems__task_object_table[TERMINA__SHARED__TASK_TABLE_SIZE];

static inline termina__rtems__task_t * termina__rtems__task__get_task(const termina__id_t task_id) {
    return &termina__rtems__task_object_table[task_id];
}

/**
 * \brief Array used to generate the names of the tasks that are
 *        created.
 */
static int8_t ntask_name[5]  = "0000";

static rtems_task termina__rtems__task__entry (rtems_task_argument arg) {

    termina__id_t * task_id = (termina__id_t *)arg;

    termina__shared__task_t * task = termina__shared__task__get_task(*task_id);

    // This function call shall never return
    task->entry(task->arg);

    return;

}

void termina__os__task__init(const termina__id_t task_id,
                             int32_t * const status) {

    *status = 0;

    termina__shared__task_t * task = termina__shared__task__get_task(task_id);
    termina__rtems__task_t * rtems_task = termina__rtems__task__get_task(task_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);
    name = rtems_build_name(ntask_name[0], ntask_name[1], ntask_name[2],
                            ntask_name[3]);

    if (rtems_task_create(name, task->priority, task->stack_size, 
                          RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES,
                          &rtems_task->rtems_task_id) != RTEMS_SUCCESSFUL) {

        *status = -1;

    }

    if (0 == *status) {

        if (rtems_task_start(rtems_task->rtems_task_id, 
                             termina__rtems__task__entry, 
                             (rtems_task_argument)&task->task_id) != RTEMS_SUCCESSFUL) {

            *status = -1;

        }

    }

    return;
}
