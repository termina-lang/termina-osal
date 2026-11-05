#include "config.h"

#include <termina.h>

#include <bsp/bootcard.h>

#if defined(TERMINA__TEST)
#include <termina/shared/test.h>
#endif

_Noreturn void termina__exec__reboot(void) {

#if defined(TERMINA__TEST)
    // A test build stops instead of restarting, and the runner stops here
    termina__os__test__halt();
#else
#ifdef TERMINA__PROFILE__DEBUG
    // Stops under gdb with the stack that led here still in place
    __asm__ __volatile__ ("ebreak");
#endif

    // Spike cannot be reset from software: the BSP powers it off through HTIF
    bsp_reset(RTEMS_FATAL_SOURCE_EXIT, 0);
#endif

}
