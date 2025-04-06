
#include <termina.h>

#include <termina/shared/interrupt.h>

void __termina_interrupt_os__init(const __termina_id_t interrupt_id,
                                  Status * const status) {
    
    status->__variant = Status__Success;

    return;

}
