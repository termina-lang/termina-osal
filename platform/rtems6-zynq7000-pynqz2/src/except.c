#include <termina.h>
#include <termina/os/rtems/except.h>

#include <stdint.h>

_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame) {

    // DFSR and DFAR for a data abort, IFSR and IFAR for a prefetch abort
    uint32_t status = 0U;
    uint32_t address = 0U;

    // The frame holds the link register of the exception mode, which is
    // ahead of the instruction that failed
    uint32_t pc = (uint32_t)(uintptr_t)frame->register_pc;

    if (ARM_EXCEPTION_DATA_ABORT == frame->vector) {
        __asm__ __volatile__ ("mrc p15, 0, %0, c5, c0, 0" : "=r" (status));
        __asm__ __volatile__ ("mrc p15, 0, %0, c6, c0, 0" : "=r" (address));
        pc = pc - 8U;
    } else if (ARM_EXCEPTION_PREF_ABORT == frame->vector) {
        __asm__ __volatile__ ("mrc p15, 0, %0, c5, c0, 1" : "=r" (status));
        __asm__ __volatile__ ("mrc p15, 0, %0, c6, c0, 2" : "=r" (address));
        pc = pc - 4U;
    } else if (ARM_EXCEPTION_UNDEF == frame->vector) {
        pc = pc - (((frame->register_cpsr & ARM_PSR_T) != 0U) ? 2U : 4U);
    }

    termina__except__processor_fault((uint32_t)frame->vector, status,
                                     (size_t)pc, (size_t)address);

}
