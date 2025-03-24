
#include <termina.h>

#include <rtems.h>

void __termina_exec__shutdown() {
    
    rtems_shutdown_executive(1);

}