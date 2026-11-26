
/**
 * @file
 * @ingroup termina__osal__platform
 *
 * @brief Entry point of the NUCLEO-L432KC board and SysTick handler.
 */

#include "hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include <termina.h>

extern void xPortSysTickHandler(void);

/**
 * @brief Entry point: initializes the hardware and the application and
 *        starts the FreeRTOS scheduler.
 *
 * If the initialization of the application fails, the system reboots.
 *
 * @return The function does not return.
 */
int main(void)
{
    termina__error_code_t status = termina__error__none;

    termina__hal__init();
    termina__hal__system_clock_config();

#if defined(TERMINA__TEST)
    termina__test__init();
#endif

    termina__app__init(&status);

    if (termina__error__none != status) {

        termina__exec__reboot();

    }

    vTaskStartScheduler();

    for (;;);
}

void termina__hal__systick_handler(void)
{
    xPortSysTickHandler();
}