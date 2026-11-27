
/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Installation of the interrupts of the POSIX emulation.
 */

#include <termina.h>

#include <termina/shared/interrupt.h>
#include <termina/os/posix/keyboard.h>

void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  termina__error_code_t * const status) {

    (void)interrupt_id;

    *status = termina__error__none;

    // Interrupt 0, the keyboard interrupt, is the only interrupt of the
    // emulation, so the identifier is not checked.

    termina__posix__keyboard__irq_init(status);

    return;

}
