
#include <termina.h>

#include <termina/os/posix/signal.h>

__termina_task_lock_t __termina_task__lock(void) {

    __posix_signal__disable();

    return 0;

}

void __termina_task__unlock(__termina_task_lock_t lock) {

    __posix_signal__enable();

}

__termina_event_lock_t __termina_event__lock(void) {

    __posix_signal__disable();

    return 0;

}

void __termina_event__unlock(__termina_event_lock_t lock) {

    __posix_signal__enable();

}