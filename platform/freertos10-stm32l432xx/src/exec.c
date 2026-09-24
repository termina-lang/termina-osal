
#include <termina.h>

#include "stm32l4xx.h"

_Noreturn void termina__exec__reboot(void)
{
#ifdef TERMINA__PROFILE__DEBUG
    // Breakpoint of Cortex-M. With no debugger attached it escalates to a
    // HardFault, which is why the reset follows it and why this is only built
    // in the debug profile.
    __BKPT(0);
#endif

    NVIC_SystemReset();
    for (;;) { }   /* defensive: the compiler does not see that
                      NVIC_SystemReset never returns */
}
