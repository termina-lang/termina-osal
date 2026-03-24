
#include "hal.h"
#include "cmsis_os.h"

#include <termina.h>

int main(void)
{
    int32_t status = 0;

    __hal_init();
    __hal_system_clock_config();

    __termina_app__init(&status);

    osKernelStart();

    for (;;);
}

void __hal_systick_handler(void)
{
    osSystickHandler();
}