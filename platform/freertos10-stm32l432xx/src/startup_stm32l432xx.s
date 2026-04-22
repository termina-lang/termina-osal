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

  .syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.thumb

.global	g_pfnVectors
.global	Default_Handler

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
	.weak	Reset_Handler
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

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
	.size	Default_Handler, .-Default_Handler
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
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	__hal_systick_handler
	.word	__hal_generic_handler	// Window Watchdog
	.word	__hal_generic_handler // PVD through EXTI Line detection
	.word	__hal_generic_handler	// Tamper and TimeStamp through the EXTI line
	.word	__hal_generic_handler // RTC Wakeup through the EXTI line
	.word	__hal_generic_handler // FLASH
	.word	__hal_generic_handler // RCC
	.word	__hal_generic_handler // EXTI Line0
	.word	__hal_generic_handler // EXTI Line1
	.word	__hal_generic_handler // EXTI Line2
	.word	__hal_generic_handler // EXTI Line3
	.word	__hal_generic_handler // EXTI Line4
	.word	__hal_generic_handler // DMA1 Channel1
	.word	__hal_generic_handler // DMA1 Channel2
	.word	__hal_generic_handler // DMA1 Channel3
	.word	__hal_generic_handler // DMA1 Channel4
	.word	__hal_generic_handler // DMA1 Channel5
	.word	__hal_generic_handler // DMA1 Channel6
	.word	__hal_generic_handler // DMA1 Channel7
	.word	__hal_generic_handler // ADC1 and ADC2
	.word	__hal_generic_handler // CAN1 TX
	.word	__hal_generic_handler // CAN1 RX0
	.word	__hal_generic_handler // CAN1 RX1
	.word	__hal_generic_handler // CAN1 SCE
	.word	__hal_generic_handler // EXTI Line[9:5]
	.word	__hal_generic_handler // TIM1 Break and TIM15
	.word	__hal_generic_handler // TIM1 Update and TIM16
	.word	__hal_generic_handler // TIM1 Trigger and Commutation and TIM17
	.word	__hal_generic_handler // TIM1 Capture Compare
	.word	__hal_generic_handler // TIM2
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // I2C1 Event
	.word	__hal_generic_handler // I2C1 Error
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // SPI1
	.word	0               // Reserved
	.word	__hal_generic_handler // USART1
	.word	__hal_generic_handler // USART2
	.word	0               // Reserved
	.word	__hal_generic_handler // EXTI Line[15:10]
	.word	__hal_generic_handler // RTC Alarm (A and B) through EXTI Line
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // SPI3
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // TIM6 and DAC underrun errors
	.word	__hal_generic_handler // TIM7
	.word	__hal_generic_handler // DMA2 Channel1
	.word	__hal_generic_handler // DMA2 Channel2
	.word	__hal_generic_handler // DMA2 Channel3
	.word	__hal_generic_handler // DMA2 Channel4
	.word	__hal_generic_handler // DMA2 Channel5
	.word	0               // Reserved
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // COMP1 and COMP2
	.word	__hal_generic_handler // LPTIM1
	.word	__hal_generic_handler // LPTIM2
	.word	__hal_generic_handler // USB event through EXTI Line
	.word	__hal_generic_handler // DMA2 Channel6
	.word	__hal_generic_handler // DMA2 Channel7
	.word	__hal_generic_handler // LPUART1
	.word	__hal_generic_handler // Quad SPI
	.word	__hal_generic_handler // I2C3 Event
	.word	__hal_generic_handler // I2C3 Error
	.word	__hal_generic_handler // SAI1
	.word	0               // Reserved
	.word	__hal_generic_handler // SWPMI1
	.word	__hal_generic_handler // TSC
	.word	0               // Reserved
	.word	0               // Reserved
	.word	__hal_generic_handler // RNG
	.word	__hal_generic_handler // FPU
	.word	__hal_generic_handler // CRS

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

.weak	NMI_Handler
.thumb_set NMI_Handler, Default_Handler

.weak	HardFault_Handler
.thumb_set HardFault_Handler, Default_Handler

.weak	MemManage_Handler
.thumb_set MemManage_Handler, Default_Handler

.weak	BusFault_Handler
.thumb_set BusFault_Handler, Default_Handler

.weak	UsageFault_Handler
.thumb_set UsageFault_Handler, Default_Handler

.weak	SVC_Handler
.thumb_set SVC_Handler, Default_Handler

.weak	DebugMon_Handler
.thumb_set DebugMon_Handler, Default_Handler

.weak	PendSV_Handler
.thumb_set PendSV_Handler, Default_Handler
