
#include <termina.h>

#include <termina/shared/interrupt.h>

void __termina_interrupt_os__init(const __termina_id_t interrupt_id,
                                  int32_t * const status) {
    
    *status = 0;

    return;

}
