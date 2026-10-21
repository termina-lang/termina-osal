
#include "config.h"

#include <termina.h>

#include <stdint.h>

// Enable Traps bit of the Processor State Register of SPARC
#define SPARC_PSR_ET 0x20U

_Noreturn void termina__exec__reboot(void) {

#ifdef TERMINA__PROFILE__DEBUG
    // Stops under gdb with the stack that led here still in place
    __asm__ __volatile__ ("ta 1");
#endif

    // No watchdog wired to the reset on this board: a trap with traps
    // disabled stops the processor in error mode
    uint32_t psr;
    __asm__ __volatile__ ("rd %%psr, %0" : "=r" (psr));
    psr &= ~SPARC_PSR_ET;
    __asm__ __volatile__ ("wr %0, %%psr\n\t"
                          "nop\n\t"
                          "nop\n\t"
                          "nop\n\t"
                          "ta 0"
                          : : "r" (psr) : "memory");

    for (;;) {
    }

}
