#include <termina.h>

#include <termina/os/freertos10/interrupt.h>

#include "FreeRTOSConfig.h"
#include "stm32l432xx.h"
#include "hal.h"

void termina__freertos__interrupt__enable(const termina__id_t interrupt_id) {

    NVIC_SetPriority((IRQn_Type)interrupt_id, 
                     configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ((IRQn_Type)interrupt_id);

}

void termina__hal__generic_handler(void) {

    /*
     * The exception number the IPSR holds counts the 16 system exceptions of
     * the Cortex-M before the first external interrupt.
     */
    termina__freertos__interrupt__dispatch((termina__id_t)((__get_IPSR() & 0x1FFU) - 16U));

}
