# Termina OSAL Makefile

CROSS:=arm-none-eabi-

CC:=$(CROSS)gcc
AS:=$(CROSS)gcc -x assembler-with-cpp

# Adding Termina OSAL header folders

# Main Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/api
# Shared Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/shared/include
# Implementation of the Termina OSAL for FreeRTOS V10
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/os/freertos10/include
# Implementation of the Termina OSAL for FreeRTOS V10 on STM32L432xx
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/include
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/CMSIS_RTOS
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/portable/GCC/ARM_CM4F/
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/include

# Adding Termina OSAL source folders


# Termina OSAL shared sources
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
# Implementation of the Termina OSAL for FreeRTOS V10
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/freertos10/src/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/freertos10/src/system/*.c)

# Platform-specific files for FreeRTOS V10 on STM32L432xx

# FreeRTOS source files
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/CMSIS_RTOS/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/FreeRTOS/Source/portable/MemMang/*.c)
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/src/hal.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/src/interrupt.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/src/main.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/src/system_init.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/src/startup_stm32l432xx.s

# Compilation flags

MCU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS+= $(MCU) -O0 -Wall -D__TERMINA_NUMBER_OF_INTERRUPTS=83 -DSTM32L432xx -Wall -fdata-sections -ffunction-sections -g3 -gdwarf-2

LDFLAGS+= -specs=nano.specs -T$(TERMINA_OSAL_DIR)/platform/freertos10-stm32l432xx/STM32L432XX_FLASH.ld -Wl,--gc-sections
