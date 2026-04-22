
#include "hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include <termina.h>

extern void xPortSysTickHandler(void);

int main(void)
{
    int32_t status = 0;

    __hal_init();
    __hal_system_clock_config();

    __termina_app__init(&status);

    vTaskStartScheduler();

    for (;;);
}

void __hal_systick_handler(void)
{
    xPortSysTickHandler();
}