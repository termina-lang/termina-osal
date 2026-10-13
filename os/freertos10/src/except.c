#include <termina.h>
#include <termina/shared/except.h>
#include <termina/os/freertos10/except.h>

#include <FreeRTOS.h>
#include <task.h>

#include <stdint.h>

void termina__os__except__init_emitter(void) {

    // Nothing to do for FreeRTOS
    return;

}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName) {

    (void)pcTaskName;

    termina__except__kernel_failure(
        TERMINA__FREERTOS__KERNEL_FAILURE__STACK_OVERFLOW,
        (size_t)(uintptr_t)xTask);

}

void termina__freertos__except__assert_failed(void) {

    termina__except__kernel_failure(
        TERMINA__FREERTOS__KERNEL_FAILURE__ASSERT,
        (size_t)(uintptr_t)__builtin_return_address(0));

}
