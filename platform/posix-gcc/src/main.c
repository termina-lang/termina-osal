/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Entry point of the POSIX emulation on a host with GCC.
 */

#include <termina.h>

#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>
#include <termina/os/posix/keyboard.h>
#include <termina/os/posix/exec.h>

#if defined(TERMINA__TEST)
#include <termina/shared/test.h>
#endif

#include <stdio.h>
#include <unistd.h>

/**
 * @brief Entry point: initializes the emulation and the application and runs
 *        the scheduler.
 *
 * A reboot restarts the program with `execvp`. In a test build, the program
 * halts instead.
 *
 * @param[in] argc  Number of arguments; unused.
 * @param[in] argv  Arguments of the program, used to restart it.
 *
 * @return -1 if the restart fails.
 */
int main(const int argc, char * const argv[]) {

    termina__error_code_t status = termina__error__none;

    (void)argc;

    // Makes the standard output line-buffered, even when it is not a terminal.
    (void)setvbuf(stdout, NULL, _IOLBF, 0);

    termina__posix__signal__init();

    termina__posix__keyboard__init();

    termina__posix__task__init_scheduler(&status);

    termina__posix__time__init();

#if defined(TERMINA__TEST)
    termina__test__init();
#endif

    if (termina__error__none == status) {

        termina__app__init(&status);

    }

    // If the initialization failed, the application restarts without starting
    // the scheduler. Otherwise the scheduler returns when the application
    // triggers a reboot.
    if (termina__error__none == status) {

        termina__posix__task__start_scheduler();

    } else {

#if !defined(TERMINA__TEST)
        termina__posix__exec__debug_stop();
#endif

    }

#if defined(TERMINA__TEST)
    // A test stops instead of restarting
    (void)argv;
    termina__os__test__halt();
#else
    // A reboot is emulated by executing the program again.
    if (execvp(argv[0], argv) == -1) {
        perror("system reboot failed");
        return -1;
    }

    return 0;
#endif

}