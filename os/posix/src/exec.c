
#include <termina.h>

#include <termina/shared/task.h>
#include <termina/os/posix/task.h>

#include <pthread.h>
#include <signal.h>

#include <execinfo.h>
#include <unistd.h>

_Noreturn void termina__exec__reboot(void) {
    
    termina__posix__signal__disable();

#ifdef TERMINA__DEBUG
    // Stop under gdb with the stack that led here still in place, and print it
    // for a run with no debugger attached. SIGTRAP with no debugger terminates
    // the process, so the restart below is not reached in that case, which is
    // the behaviour of a host build and not of a target.
    void * buffer[128];
    int traces = backtrace(buffer, 128);
    backtrace_symbols_fd(buffer, traces, STDERR_FILENO);

    raise(SIGTRAP);
#endif

    // Wake up the main task
    pthread_kill(termina__posix__main_task_pthread, SIGUSR1);

    // Suspend current task
    termina__posix__task__suspend(termina__posix__task__get_task(termina__posix__current_task_id));

    // This code is never reached, but it is here to avoid a warning
    for (;;) { }

}
