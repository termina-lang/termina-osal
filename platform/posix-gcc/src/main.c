#include <termina.h>

#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>

#include <stdio.h>
#include <unistd.h>

int main(const int argc, char * const argv[]) {

    int32_t status = 0;

    __posix_signal__init();

    __posix_task__init_scheduler(&status);

    __posix_time__init();

    __termina_app__init(&status);

    // If this function returns, it means that the application
    // has triggered a reboot
    __posix_task__start_scheduler();

    // We simulate a reboot by restarting the application
    printf("\033[1;31m[reboot]\033[0m Restarting application...\n");
    if (execvp(argv[0], argv) == -1) {
        perror("system reboot failed");
        return -1;
    }

    return 0;

}