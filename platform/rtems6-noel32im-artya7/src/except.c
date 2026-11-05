#include <termina.h>
#include <termina/os/rtems/except.h>

#include <stdint.h>

_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame) {

    // The frame does not keep mtval, and no other trap has been taken since.
    // Zicsr is not in -march=rv32im, so it is enabled for this instruction
    // alone, as the headers of RTEMS do.
    uintptr_t address;
    __asm__ __volatile__ (".option push\n.option arch, +zicsr\ncsrr %0, mtval\n.option pop"
                          : "=r" (address));

    // mepc is the instruction that failed; RISC-V has no fault status register
    termina__except__processor_fault((uint32_t)frame->mcause, 0U,
                                     (size_t)frame->Interrupt_frame.mepc,
                                     (size_t)address);

}
