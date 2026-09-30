#ifndef TERMINA__OS__FREERTOS10__TASKS_C_ADDITIONS_H__
#define TERMINA__OS__FREERTOS10__TASKS_C_ADDITIONS_H__

/*
 * tasks.c includes this file at its end (configINCLUDE_FREERTOS_TASK_C_ADDITIONS_H),
 * where the tick count of the kernel and the number of times it has wrapped
 * around, both static to tasks.c, are in scope.
 */

#include <termina/os/freertos10/time.h>

/**
 * \brief Reads the tick count and the number of times it has wrapped around.
 *
 * The tick interrupt changes both together, so they are read under a critical
 * section. Callable from a task and from an interrupt.
 */
void termina__freertos__read_tick_count(BaseType_t * const overflows,
                                        TickType_t * const ticks)
{
    if (xPortIsInsideInterrupt() != pdFALSE) {

        UBaseType_t saved = taskENTER_CRITICAL_FROM_ISR();
        *overflows = xNumOfOverflows;
        *ticks = xTickCount;
        taskEXIT_CRITICAL_FROM_ISR(saved);

    } else {

        taskENTER_CRITICAL();
        *overflows = xNumOfOverflows;
        *ticks = xTickCount;
        taskEXIT_CRITICAL();

    }
}

#endif // TERMINA__OS__FREERTOS10__TASKS_C_ADDITIONS_H__
