#include <termina.h>

#include <stdint.h>

// System Level Control Registers of the Zynq-7000 (UG585, appendix B.28)
#define SLCR_UNLOCK       (*(volatile uint32_t *)0xF8000008U)
#define SLCR_PSS_RST_CTRL (*(volatile uint32_t *)0xF8000200U)

#define SLCR_UNLOCK_KEY   0xDF0DU
#define PSS_RST_CTRL_SOFT_RST 0x1U

_Noreturn void termina__exec__reboot(void) {

#ifdef TERMINA__PROFILE__DEBUG
    // Stops under gdb with the stack that led here still in place
    __asm__ __volatile__ ("bkpt #0");
#endif

    // Software reset of the whole PS
    for (;;) {
        SLCR_UNLOCK = SLCR_UNLOCK_KEY;
        SLCR_PSS_RST_CTRL = PSS_RST_CTRL_SOFT_RST;
    }

}
