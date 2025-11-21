
#include <termina.h>

#include <FreeRTOS.h>
#include "task.h"

// TODO: Implement a proper shutdown or reboot mechanism for FreeRTOS

_Noreturn void __termina_exec__reboot() {

    // Disable all interrupts
    taskDISABLE_INTERRUPTS();

    // A proper shutdown mechanism should be implemented here.
    for (;;) {

    }
}
