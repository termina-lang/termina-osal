
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
                              termina__error_code_t * const status) {
    
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
        *status = termina__error__os_failure;
    }

    return;

}

void termina__os__mutex__lock(const termina__id_t mutex_id,
                              termina__error_code_t * const status) {
    
    termina__rtems__mutex_t * rtems_mutex = termina__rtems__mutex__get_mutex(mutex_id);

    *status = termina__error__none;

    rtems_status_code obtain_status = rtems_semaphore_obtain(rtems_mutex->rtems_mutex_id,
                                                             RTEMS_WAIT, RTEMS_NO_TIMEOUT);

    // RTEMS 5 reports a ceiling violation on a priority ceiling mutex as an
    // invalid priority.
    if (RTEMS_INVALID_PRIORITY == obtain_status) {

        *status = termina__error__ceiling_violated;

    } else if (RTEMS_SUCCESSFUL != obtain_status) {

        *status = termina__error__os_failure;

    } else {

        // The caller holds the mutex.

    }

    return;

}

void termina__os__mutex__unlock(const termina__id_t mutex_id,
                                termina__error_code_t * const status) {
    
    termina__rtems__mutex_t * rtems_mutex = termina__rtems__mutex__get_mutex(mutex_id);

    *status = termina__error__none;

    rtems_status_code release_status = rtems_semaphore_release(rtems_mutex->rtems_mutex_id);

    if (RTEMS_NOT_OWNER_OF_RESOURCE == release_status) {

        *status = termina__error__not_owner;

    } else if (RTEMS_SUCCESSFUL != release_status) {

        *status = termina__error__os_failure;

    } else {

        // The mutex is free or held by the next task.

    }

    return;

}
