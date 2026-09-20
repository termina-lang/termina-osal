
#include "hal.h"
#include "FreeRTOS.h"
#include "task.h"

#include <termina.h>

extern void xPortSysTickHandler(void);

int main(void)
{
    int32_t status = 0;

    termina__hal__init();
    termina__hal__system_clock_config();

    termina__app__init(&status);

    vTaskStartScheduler();

    for (;;);
}

void termina__hal__systick_handler(void)
{
    xPortSysTickHandler();
}