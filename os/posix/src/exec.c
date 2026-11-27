
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Reboot, quiesce and debug stop of the POSIX emulation.
 */

#include "config.h"

#include <termina.h>

#include <termina/shared/task.h>
#include <termina/shared/exec.h>
#include <termina/os/posix/task.h>
#include <termina/os/posix/exec.h>
#include <termina/os/posix/signal.h>

#include <pthread.h>
#include <signal.h>

#include <execinfo.h>
#include <unistd.h>

void termina__posix__exec__debug_stop(void) {

#ifdef TERMINA__PROFILE__DEBUG
    // Prints the stack and raises SIGTRAP, which stops the program under gdb
    // with the stack still in place. The runtime blocks SIGTRAP, so the
    // function unblocks it first. With no debugger attached, SIGTRAP
    // terminates the process and the restart is not reached.
    void * buffer[128];
    int traces = backtrace(buffer, 128);
    backtrace_symbols_fd(buffer, traces, STDERR_FILENO);

    sigset_t trap_set;
    sigemptyset(&trap_set);
    sigaddset(&trap_set, SIGTRAP);
    pthread_sigmask(SIG_UNBLOCK, &trap_set, NULL);

    raise(SIGTRAP);
#endif

}

void termina__os__exec__quiesce(void) {

    // Blocks the signals, which emulate the interrupts of the target. The
    // operations in progress are left unfinished.
    termina__posix__signal__disable();

}

_Noreturn void termina__exec__reboot(void) {

    termina__posix__signal__disable();

#if !defined(TERMINA__TEST)
    // A test build does not raise SIGTRAP.
    termina__posix__exec__debug_stop();
#endif

    // Wakes up the main task.
    pthread_kill(termina__posix__main_task_pthread, SIGUSR1);

    // Suspends the current task.
    termina__posix__task__suspend(termina__posix__task__get_task(termina__posix__current_task_id));

    // This code is never reached, but it is here to avoid a warning
    for (;;) { }

}
