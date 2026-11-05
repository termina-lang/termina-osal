#include "config.h"

#include <termina.h>

#include <rtems.h>

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

    // No reset wired that software reaches: with interrupts disabled, the
    // processor waits for ever
    rtems_interrupt_level level;
    rtems_interrupt_local_disable(level);
    (void)level;

    for (;;) {
        __asm__ __volatile__ ("wfi");
    }
#endif

}
