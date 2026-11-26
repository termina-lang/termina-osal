/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Processor faults of the LEON3 on RTEMS 5, raised as
 *        `EProcessorFault`.
 */

#include <termina.h>
#include <termina/os/rtems/except.h>

#include <stdint.h>

_Noreturn void termina__rtems__platform__processor_fault(
    const CPU_Exception_frame * const frame) {

    // The frame of RTEMS 5 on SPARC keeps the PC in the interrupt frame, and
    // the LEON3 gives no fault address
    termina__except__processor_fault(frame->trap, 0U, (size_t)frame->isf->pc,
                                     0U);

}
