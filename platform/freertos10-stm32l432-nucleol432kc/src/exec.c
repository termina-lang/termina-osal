
#include "config.h"

#include <termina.h>

#include "stm32l4xx.h"

#if defined(TERMINA__TEST)
#include <termina/shared/test.h>
#endif

_Noreturn void termina__exec__reboot(void)
{
#if defined(TERMINA__TEST)
    // A test build stops instead of restarting, and the runner stops here
    termina__os__test__halt();
#else
#ifdef TERMINA__PROFILE__DEBUG
    // Stops under gdb with the stack that led here still in place
    __BKPT(0);
#endif

    NVIC_SystemReset();
    for (;;) { }   /* defensive: the compiler does not see that
                      NVIC_SystemReset never returns */
#endif
}
