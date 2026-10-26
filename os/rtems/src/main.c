
#include <rtems.h>

#include "config.h"

#include <termina.h>
#include <termina/os/rtems/except.h>

#define TERMINA__APP_CONFIG__MESSAGE_QUEUE_BUFFER CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE

#define CONFIGURE_MAXIMUM_TASKS (TERMINA__APP_CONFIG__TASKS + 1)
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES (TERMINA__APP_CONFIG__MESSAGE_QUEUES)
#define CONFIGURE_MAXIMUM_TIMERS (TERMINA__APP_CONFIG__PERIODIC_TIMERS)
#define CONFIGURE_MAXIMUM_SEMAPHORES (TERMINA__APP_CONFIG__MUTEXES)

#define CONFIGURE_MESSAGE_BUFFER_MEMORY TERMINA__APP_CONFIG__MESSAGE_BUFFER_MEMORY

#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MICROSECONDS_PER_TICK (TERMINA__TIME__MICROSECONDS_PER_TICK)

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

// Only on RTEMS 6, whose stack checker takes the reporter of the OSAL
#if __RTEMS_MAJOR__ >= 6
#define CONFIGURE_STACK_CHECKER_ENABLED
#define CONFIGURE_STACK_CHECKER_REPORTER termina__rtems__except__stack_overflow
#endif

// Fatal errors of RTEMS enter the fatal path of the runtime
#define CONFIGURE_INITIAL_EXTENSIONS \
    { .fatal = termina__rtems__except__fatal_extension }

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

rtems_task Init(rtems_task_argument _ignored) {

    termina__error_code_t status = termina__error__none;

    (void)_ignored;

#if defined(TERMINA__TEST)
    termina__test__init();
#endif

    termina__app__init(&status);

    if (termina__error__none != status) {

        termina__exec__reboot();

    }

    rtems_task_delete(RTEMS_SELF);

}
