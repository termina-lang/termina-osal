
#include <termina.h>

#include <rtems.h>

_Noreturn void termina__exec__reboot(void) {

#ifdef TERMINA__PROFILE__DEBUG
    // Breakpoint instruction of ARM, which stops the program under gdb with
    // the stack that led here still in place. The reset follows it, so a
    // build with no debugger attached restarts as it does in release.
    __asm__ __volatile__ ("bkpt #0");
#endif

    rtems_shutdown_executive(1);

}
