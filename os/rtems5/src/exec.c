
#include <termina.h>

#include <rtems.h>

_Noreturn void __termina_exec__shutdown() {
    
    rtems_shutdown_executive(1);

}

_Noreturn void __termina_exec__reboot() {

    __termina_exec__shutdown();

}
