/*
 * FreeRTOSConfig.h - FreeRTOS configuration for termina-osal
 *
 * Kernel: FreeRTOS V10.3.1 (tag `V10.3.1-kernel-only`).
 * Derived from the FreeRTOS sample configuration. FreeRTOS is distributed
 * under the MIT license; see the upstream kernel tree for the full notice.
 *
 * Part of the port `platform/freertos10-stm32l432xx/`. Values are tuned for
 * the Termina runtime semantics; the sections below group the knobs by
 * concern and carry rationale where it is not self-evident.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* config.h is emitted by the Termina transpiler and provides application
 * macros referenced below (notably __TERMINA_MICROSECONDS_PER_TICK). */
#include "config.h"

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>
extern uint32_t SystemCoreClock;
#endif


/* ----------------------------------------------------------------------- */
/* Scheduler                                                               */
/* ----------------------------------------------------------------------- */

#define configUSE_PREEMPTION                    1
/* Strict fixed-priority scheduling: no round-robin among equal-priority
 * tasks. Termina is a hard real-time model and relies on deterministic
 * preemption ordering. */
#define configUSE_TIME_SLICING                  0
#define configIDLE_SHOULD_YIELD                 1
/* 256 levels cover the full range of __termina_task_prio_t (uint8_t), so
 * priority2freertos() in os/freertos10/include/.../priority.h maps one to
 * one. The runtime reserves Termina priority 0 for itself (see the timers
 * section below). */
#define configMAX_PRIORITIES                    ( 256 )
#define configMINIMAL_STACK_SIZE                ( ( uint16_t ) 128 )
#define configUSE_16_BIT_TICKS                  0


/* ----------------------------------------------------------------------- */
/* Timing                                                                  */
/* ----------------------------------------------------------------------- */

#define configCPU_CLOCK_HZ                      ( SystemCoreClock )
#define configTICK_RATE_HZ \
    ( ( TickType_t ) ( 1000000U / __TERMINA_MICROSECONDS_PER_TICK ) )


/* ----------------------------------------------------------------------- */
/* Memory                                                                  */
/* ----------------------------------------------------------------------- */

/* Heap used by heap_1.c. Sized for the OBDH application; raise if a larger
 * application needs more kernel objects or task stacks. */
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 16384 ) )


/* ----------------------------------------------------------------------- */
/* Primitives                                                              */
/* ----------------------------------------------------------------------- */

#define configUSE_MUTEXES                       1
/* Termina mutexes are IPCP-emulated by priority elevation
 * (os/freertos10/src/mutex.c); recursive mutexes are never requested. */
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8
#define configMAX_TASK_NAME_LEN                 16


/* ----------------------------------------------------------------------- */
/* Software timers                                                         */
/* ----------------------------------------------------------------------- */

#define configUSE_TIMERS                        1
/* Termina's periodic_timer semantics requires the daemon to preempt every
 * application task, so it sits at the top FreeRTOS priority. This reserves
 * Termina priority 0 (the highest, mapped by priority.h to FreeRTOS
 * configMAX_PRIORITIES - 1) for the runtime: no application task may use
 * it. */
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 )


/* ----------------------------------------------------------------------- */
/* Hooks and debugging (all disabled)                                      */
/* ----------------------------------------------------------------------- */

#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_APPLICATION_TASK_TAG          0
#define configUSE_TRACE_FACILITY                1
#define configGENERATE_RUN_TIME_STATS           0


/* ----------------------------------------------------------------------- */
/* Co-routines (disabled)                                                  */
/* ----------------------------------------------------------------------- */

#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )


/* ----------------------------------------------------------------------- */
/* INCLUDE_* - API functions compiled into the kernel                      */
/* ----------------------------------------------------------------------- */

#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xQueueGetMutexHolder            1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_eTaskGetState                   1


/* ----------------------------------------------------------------------- */
/* Cortex-M specifics                                                      */
/* ----------------------------------------------------------------------- */

#ifdef __NVIC_PRIO_BITS
#define configPRIO_BITS                         __NVIC_PRIO_BITS
#else
#define configPRIO_BITS                         4   /* 15 priority levels */
#endif

/* Lowest priority usable by the kernel / application. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         0xF
/* Highest priority at which an ISR may call FreeRTOS "FromISR" API.
 * All IRQs registered by the Termina runtime (§3.7 of the thesis outline)
 * use this exact level so that irq_lock reliably masks them via BASEPRI. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* Kernel-facing shifted values, derived from the library-facing ones. */
#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )


/* ----------------------------------------------------------------------- */
/* Kernel port aliases                                                     */
/* ----------------------------------------------------------------------- */

/* SVC and PendSV vectors in startup_stm32l432xx.s bind to these standard
 * Cortex-M names; the FreeRTOS port provides the strong implementations
 * (vPortSVCHandler in port.c, xPortPendSVHandler in port.c). */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler


/* ----------------------------------------------------------------------- */
/* Assert                                                                  */
/* ----------------------------------------------------------------------- */

#define configASSERT( x ) \
    if ( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for ( ;; ); }


#endif /* FREERTOS_CONFIG_H */
