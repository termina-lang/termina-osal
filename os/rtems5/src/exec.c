
#include <termina.h>

#include <rtems.h>

_Noreturn void __termina_exec__reboot(void) {

    rtems_shutdown_executive(1);

}
