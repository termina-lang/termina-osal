
#include <termina.h>

#include <termina/os/posix/task.h>
#include <termina/os/posix/time.h>

int main() {

    int32_t status = 0;

    __posix_signal__init();

    __posix_task__init_scheduler(&status);

    __posix_time__init();

    __termina_app__init(&status);

    __posix_task__start_scheduler();

    return 0;

}