
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>

#include <execinfo.h>
#include <unistd.h>

void __termina_exec__shutdown() {
    
    __posix_signal__disable();
    
    // Obtain and print the call stack
    void * buffer[128];
    int traces = backtrace(buffer, 128);
    backtrace_symbols_fd(buffer, traces, STDERR_FILENO);

    // Wake up the main task
    pthread_kill(__posix_main_task_pthread, SIGUSR1);

    // Suspend current task
    __posix_task__suspend(__posix_task__get_task(__posix_current_task_id));

}