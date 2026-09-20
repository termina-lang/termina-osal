
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/mutex.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_mutex_id;

} termina__rtems__mutex_t;

static termina__rtems__mutex_t termina__rtems__mutex_object_table[TERMINA__SHARED__MUTEX_TABLE_SIZE];

static inline termina__rtems__mutex_t * termina__rtems__mutex__get_mutex(const termina__id_t mutex_id) {
    return &termina__rtems__mutex_object_table[mutex_id];
}

/**
 * \brief Array used to generate the names of the mutexes that are
 *        created.
 */
static int8_t nmutex_name[5]  = "0000";

void termina__os__mutex__init(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__shared__mutex_t * mutex = termina__shared__mutex__get_mutex(mutex_id);
    termina__rtems__mutex_t * rtems_mutex = termina__rtems__mutex__get_mutex(mutex_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(nmutex_name[0], nmutex_name[1], nmutex_name[2],
                     nmutex_name[3]);
    name = rtems_build_name(nmutex_name[0], nmutex_name[1], nmutex_name[2],
                            nmutex_name[3]);
    
    if (rtems_semaphore_create(name, 1, RTEMS_BINARY_SEMAPHORE 
                               | RTEMS_PRIORITY 
                               | RTEMS_PRIORITY_CEILING,
                           mutex->protocol.Ceiling._0, &rtems_mutex->rtems_mutex_id) != RTEMS_SUCCESSFUL) {
        *status = -1;
    }

    return;

}

void termina__os__mutex__lock(const termina__id_t mutex_id,
                              int32_t * const status) {
    
    termina__rtems__mutex_t * rtems_mutex = termina__rtems__mutex__get_mutex(mutex_id);

    *status = 0;

    if (rtems_semaphore_obtain(rtems_mutex->rtems_mutex_id, RTEMS_WAIT, 
                               RTEMS_NO_TIMEOUT) != RTEMS_SUCCESSFUL) {

        *status = -1;

    }

    return;

}

void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                int32_t * const status) {
    
    termina__rtems__mutex_t * rtems_mutex = termina__rtems__mutex__get_mutex(mutex_id);

    *status = 0;

    if (rtems_semaphore_release(rtems_mutex->rtems_mutex_id) != RTEMS_SUCCESSFUL) {

        *status = -1;

    }

    return;

}
