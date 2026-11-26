/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Processor faults of the NOEL-V RV32IM on RTEMS 6, raised as
 *        `EProcessorFault`.
 */

#include <termina.h>
#include <termina/os/rtems/except.h>

#include <stdint.h>

_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame) {

    // The frame does not keep mtval, and no other trap has been taken since.
    uintptr_t address;
    __asm__ __volatile__ ("csrr %0, mtval" : "=r" (address));

    // mepc is the instruction that failed; RISC-V has no fault status register
    termina__except__processor_fault((uint32_t)frame->mcause, 0U,
                                     (size_t)frame->Interrupt_frame.mepc,
                                     (size_t)address);

}
