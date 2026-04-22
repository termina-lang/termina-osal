
#include <termina.h>

#include "stm32l4xx.h"

_Noreturn void __termina_exec__reboot(void)
{
    NVIC_SystemReset();
    for (;;) { }   /* defensive: the compiler does not see that
                      NVIC_SystemReset never returns */
}
