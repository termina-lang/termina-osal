
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>

#include <execinfo.h>
#include <unistd.h>

_Noreturn void termina__exec__reboot(void) {
    
    termina__posix__signal__disable();
    
    // Obtain and print the call stack
    void * buffer[128];
    int traces = backtrace(buffer, 128);
    backtrace_symbols_fd(buffer, traces, STDERR_FILENO);

    // Wake up the main task
    pthread_kill(termina__posix__main_task_pthread, SIGUSR1);

    // Suspend current task
    termina__posix__task__suspend(termina__posix__task__get_task(termina__posix__current_task_id));

    // This code is never reached, but it is here to avoid a warning
    for (;;) { }

}
