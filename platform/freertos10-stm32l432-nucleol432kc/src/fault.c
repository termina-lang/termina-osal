/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Handler of the processor exceptions of the STM32L432xx, which raises
 *        `EProcessorFault`.
 */

#include <termina.h>

#include "stm32l4xx.h"

#include <stdint.h>

void termina__hal__fault_raise(const uint32_t * const frame);
void termina__hal__fault_handler(void);

/**
 * @brief Raises `EProcessorFault` with the data of the exception.
 *
 * The exception carries the exception number of the IPSR (2 for the NMI, 3 for
 * the HardFault, 4 to 6 for MemManage, BusFault and UsageFault, 12 for
 * DebugMon), the CFSR, the stacked PC and, when valid, the MMFAR or the BFAR.
 * MemManage, BusFault and UsageFault are not enabled, so they escalate to the
 * HardFault, and the CFSR tells them apart.
 *
 * @param[in] frame  Exception frame stacked by the processor.
 */
void termina__hal__fault_raise(const uint32_t * const frame) {

    const uint32_t number = __get_IPSR() & 0x1FFU;
    const uint32_t cfsr = SCB->CFSR;
    uint32_t address = 0U;

    if (0U != (cfsr & SCB_CFSR_MMARVALID_Msk)) {
        address = SCB->MMFAR;
    } else if (0U != (cfsr & SCB_CFSR_BFARVALID_Msk)) {
        address = SCB->BFAR;
    }

    // The stacked frame is r0-r3, r12, lr, pc, xpsr
    termina__except__processor_fault(number, cfsr,
                                     (size_t)frame[6], (size_t)address);

}

/**
 * @brief Entry of the vector table for the processor exceptions, which passes
 *        the stacked frame to termina__hal__fault_raise().
 */
// The frame is on the main or the process stack, as bit 2 of EXC_RETURN says
__attribute__((naked)) void termina__hal__fault_handler(void) {

    __asm__ __volatile__ (
        "tst lr, #4\n\t"
        "ite eq\n\t"
        "mrseq r0, msp\n\t"
        "mrsne r0, psp\n\t"
        "b termina__hal__fault_raise\n\t");

}
