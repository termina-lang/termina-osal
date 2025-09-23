
#include <termina.h>

#include <termina/shared/interrupt.h>
#include <termina/os/posix/keyboard.h>

void __termina_interrupt_os__init(const __termina_id_t interrupt_id,
                                  int32_t * const status) {
    
    *status = 0;

    // For the time being, only interrupt 0 (kbd_irq) is available.
    // If we are here, it means that (interrupt_id == 0), so we do
    // not need to check it.

    __posix_keyboard__irq_init(status);

    return;

}
