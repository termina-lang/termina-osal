#include <termina.h>

#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>
#include <termina/os/posix/keyboard.h>

#include <stdio.h>
#include <unistd.h>

int main(const int argc, char * const argv[]) {

    int32_t status = 0;

    (void)argc;

    // Line-buffer stdout also when it is not a terminal.
    (void)setvbuf(stdout, NULL, _IOLBF, 0);

    termina__posix__signal__init();

    termina__posix__keyboard__init();

    termina__posix__task__init_scheduler(&status);

    termina__posix__time__init();

    if (0 == status) {

        termina__app__init(&status);

    }

    // If the initialization failed, the application restarts without starting
    // the scheduler. Otherwise the scheduler returns when the application
    // triggers a reboot.
    if (0 == status) {

        termina__posix__task__start_scheduler();

    }

    // We simulate a reboot by restarting the application
    printf("\033[1;31m[reboot]\033[0m Restarting application...\n");
    if (execvp(argv[0], argv) == -1) {
        perror("system reboot failed");
        return -1;
    }

    return 0;

}