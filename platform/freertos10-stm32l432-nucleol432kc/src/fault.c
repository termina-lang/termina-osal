#include <termina.h>

#include "stm32l4xx.h"

#include <stdint.h>

// Exception number of the HardFault. MemManage, BusFault and UsageFault are
// not enabled, so they escalate to it, and CFSR tells them apart.
#define HARDFAULT_EXCEPTION_NUMBER 3U

void termina__hal__hardfault_raise(const uint32_t * const frame);
void termina__hal__hardfault_handler(void);

void termina__hal__hardfault_raise(const uint32_t * const frame) {

    const uint32_t cfsr = SCB->CFSR;
    uint32_t address = 0U;

    if (0U != (cfsr & SCB_CFSR_MMARVALID_Msk)) {
        address = SCB->MMFAR;
    } else if (0U != (cfsr & SCB_CFSR_BFARVALID_Msk)) {
        address = SCB->BFAR;
    }

    // The stacked frame is r0-r3, r12, lr, pc, xpsr
    termina__except__processor_fault(HARDFAULT_EXCEPTION_NUMBER, cfsr,
                                     (size_t)frame[6], (size_t)address);

}

// The frame is on the main or the process stack, as bit 2 of EXC_RETURN says
__attribute__((naked)) void termina__hal__hardfault_handler(void) {

    __asm__ __volatile__ (
        "tst lr, #4\n\t"
        "ite eq\n\t"
        "mrseq r0, msp\n\t"
        "mrsne r0, psp\n\t"
        "b termina__hal__hardfault_raise\n\t");

}
