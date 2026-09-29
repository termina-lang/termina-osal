
#include <termina.h>

#include <termina/shared/interrupt.h>
#include <termina/os/posix/keyboard.h>

void termina__interrupt_os__init(const termina__id_t interrupt_id,
                                  termina__error_code_t * const status) {

    (void)interrupt_id;

    *status = termina__error__none;

    // For the time being, only interrupt 0 (kbd_irq) is available.
    // If we are here, it means that (interrupt_id == 0), so we do
    // not need to check it.

    termina__posix__keyboard__irq_init(status);

    return;

}
