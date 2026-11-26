/**
  ******************************************************************************
  * @file      startup_stm32l432xx.s
  * @author    MCD Application Team
  * @brief     STM32L432xx devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address,
  *                - Configure the clock system  
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Copyright (c) The Termina Project Contributors
 *
 * Modified from Source/Templates/gcc/startup_stm32l432xx.s of cmsis_device_l4
 * v1.7.4 (https://github.com/STMicroelectronics/cmsis_device_l4), whose
 * LICENSE.md is in vendor/cmsis-device-l4-1: the vector table sends the
 * processor exceptions, the SysTick and every interrupt to the handlers of the
 * OSAL (termina__hal__fault_handler, termina__hal__systick_handler and
 * termina__hal__generic_handler), and SVC and PendSV to those of FreeRTOS. It
 * has no weak symbols and no default handler. */

  .syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.thumb

.global	g_pfnVectors

/* start address for the initialization values of the .data section.
defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

.equ  BootRAM,        0xF1E0F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section	.text.Reset_Handler
	.global	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack    /* Set stack pointer */

/* Call the clock system initialization function.*/
    bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
	bl	main

LoopForever:
    b LoopForever
    
.size	Reset_Handler, .-Reset_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex-M4.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
	.word	_estack
	.word	Reset_Handler
	.word	termina__hal__fault_handler	// NMI
	.word	termina__hal__fault_handler	// HardFault
	.word	termina__hal__fault_handler	// MemManage
	.word	termina__hal__fault_handler	// BusFault
	.word	termina__hal__fault_handler	// UsageFault
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler	// vPortSVCHandler of FreeRTOS
	.word	termina__hal__fault_handler	// DebugMon
	.word	0
	.word	PendSV_Handler	// xPortPendSVHandler of FreeRTOS
	.word	termina__hal__systick_handler
	.word	termina__hal__generic_handler	// Window Watchdog
	.word	termina__hal__generic_handler // PVD through EXTI Line detection
	.word	termina__hal__generic_handler	// Tamper and TimeStamp through the EXTI line
	.word	termina__hal__generic_handler // RTC Wakeup through the EXTI line
	.word	termina__hal__generic_handler // FLASH
	.word	termina__hal__generic_handler // RCC
	.word	termina__hal__generic_handler // EXTI Line0
	.word	termina__hal__generic_handler // EXTI Line1
	.word	termina__hal__generic_handler // EXTI Line2
	.word	termina__hal__generic_handler // EXTI Line3
	.word	termina__hal__generic_handler // EXTI Line4
	.word	termina__hal__generic_handler // DMA1 Channel1
	.word	termina__hal__generic_handler // DMA1 Channel2
	.word	termina__hal__generic_handler // DMA1 Channel3
	.word	termina__hal__generic_handler // DMA1 Channel4
	.word	termina__hal__generic_handler // DMA1 Channel5
	.word	termina__hal__generic_handler // DMA1 Channel6
	.word	termina__hal__generic_handler // DMA1 Channel7
	.word	termina__hal__generic_handler // ADC1 and ADC2
	.word	termina__hal__generic_handler // CAN1 TX
	.word	termina__hal__generic_handler // CAN1 RX0
	.word	termina__hal__generic_handler // CAN1 RX1
	.word	termina__hal__generic_handler // CAN1 SCE
	.word	termina__hal__generic_handler // EXTI Line[9:5]
	.word	termina__hal__generic_handler // TIM1 Break and TIM15
	.word	termina__hal__generic_handler // TIM1 Update and TIM16
	.word	termina__hal__generic_handler // TIM1 Trigger and Commutation and TIM17
	.word	termina__hal__generic_handler // TIM1 Capture Compare
	.word	termina__hal__generic_handler // TIM2
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // I2C1 Event
	.word	termina__hal__generic_handler // I2C1 Error
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // SPI1
	.word	0               // Reserved
	.word	termina__hal__generic_handler // USART1
	.word	termina__hal__generic_handler // USART2
	.word	0               // Reserved
	.word	termina__hal__generic_handler // EXTI Line[15:10]
	.word	termina__hal__generic_handler // RTC Alarm (A and B) through EXTI Line
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // SPI3
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // TIM6 and DAC underrun errors
	.word	termina__hal__generic_handler // TIM7
	.word	termina__hal__generic_handler // DMA2 Channel1
	.word	termina__hal__generic_handler // DMA2 Channel2
	.word	termina__hal__generic_handler // DMA2 Channel3
	.word	termina__hal__generic_handler // DMA2 Channel4
	.word	termina__hal__generic_handler // DMA2 Channel5
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // COMP1 and COMP2
	.word	termina__hal__generic_handler // LPTIM1
	.word	termina__hal__generic_handler // LPTIM2
	.word	termina__hal__generic_handler // USB event through EXTI Line
	.word	termina__hal__generic_handler // DMA2 Channel6
	.word	termina__hal__generic_handler // DMA2 Channel7
	.word	termina__hal__generic_handler // LPUART1
	.word	termina__hal__generic_handler // Quad SPI
	.word	termina__hal__generic_handler // I2C3 Event
	.word	termina__hal__generic_handler // I2C3 Error
	.word	termina__hal__generic_handler // SAI1
	.word	0               // Reserved
	.word	termina__hal__generic_handler // SWPMI1
	.word	termina__hal__generic_handler // TSC
	.word	0               // Reserved
	.word	0               // Reserved
	.word	termina__hal__generic_handler // RNG
	.word	termina__hal__generic_handler // FPU
	.word	termina__hal__generic_handler // CRS
