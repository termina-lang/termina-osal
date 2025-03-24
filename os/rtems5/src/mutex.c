
#include <termina.h>

#include <termina/shared/list.h>
#include <termina/shared/task.h>
#include <termina/shared/mutex.h>

#include <termina/os/rtems5/name.h>

#include <rtems.h>

typedef struct {

    rtems_id rtems_mutex_id;

} __rtems_mutex_t;

static __rtems_mutex_t __rtems_mutex_object_table[__TERMINA_APP_CONFIG_MUTEXES];

static inline __rtems_mutex_t * __rtems_mutex__get_mutex(const __termina_id_t mutex_id) {
    return &__rtems_mutex_object_table[mutex_id];
}

/**
 * \brief Array used to generate the names of the mutexes that are
 *        created.
 */
static int8_t nmutex_name[5]  = "0000";

void __termina_os_mutex__init(const __termina_id_t mutex_id,
                              Status * const status) {
    
    __termina_shared_mutex_t * mutex = __termina_shared_mutex__get_mutex(mutex_id);
    __rtems_mutex_t * rtems_mutex = __rtems_mutex__get_mutex(mutex_id);

    rtems_name name;                        
                                            
    NEXT_OBJECT_NAME(nmutex_name[0], nmutex_name[1], nmutex_name[2],
            nmutex_name[3]);
    name = rtems_build_name(nmutex_name[0], nmutex_name[1], nmutex_name[2],
                            nmutex_name[3]);
    
    if (rtems_semaphore_create(name, 1, RTEMS_BINARY_SEMAPHORE 
                               | RTEMS_PRIORITY 
                               | RTEMS_PRIORITY_CEILING,
                           mutex->prio_ceiling, &rtems_mutex->rtems_mutex_id) != RTEMS_SUCCESSFUL) {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    return;

}

void __termina_os_mutex__lock(const __termina_id_t mutex_id,
                              Status * const status) {
    
    __rtems_mutex_t * rtems_mutex = __rtems_mutex__get_mutex(mutex_id);

    status->__variant = Status__Success;

    if (rtems_semaphore_obtain(rtems_mutex->rtems_mutex_id, RTEMS_WAIT, 
                               RTEMS_NO_TIMEOUT) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    return;

}

void __termina_os_mutex__unlock(const __termina_id_t mutex_id,
                                Status * const status) {
    
    __rtems_mutex_t * rtems_mutex = __rtems_mutex__get_mutex(mutex_id);

    status->__variant = Status__Success;

    if (rtems_semaphore_release(rtems_mutex->rtems_mutex_id) != RTEMS_SUCCESSFUL) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    return;

}