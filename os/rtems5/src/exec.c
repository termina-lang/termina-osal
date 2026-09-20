
#include <termina.h>

#include <rtems.h>

_Noreturn void termina__exec__reboot(void) {

    rtems_shutdown_executive(1);

}
