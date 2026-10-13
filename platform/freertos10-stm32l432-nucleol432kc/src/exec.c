
#include <termina.h>

#include "stm32l4xx.h"

_Noreturn void termina__exec__reboot(void)
{
#ifdef TERMINA__PROFILE__DEBUG
    // Stops under gdb with the stack that led here still in place
    __BKPT(0);
#endif

    NVIC_SystemReset();
    for (;;) { }   /* defensive: the compiler does not see that
                      NVIC_SystemReset never returns */
}
