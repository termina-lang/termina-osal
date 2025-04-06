# Termina OSAL Makefile

CROSS:=

CC:=$(CROSS)gcc

# Adding Termina OSAL header folders

# Main Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/api
# Shared Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/shared/include
# Implementation of the Termina OSAL for POSIX
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/os/posix/include
# Implementation of the Termina OSAL for POSIX GICC
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/posix-gcc/include

# Adding Termina OSAL source folders

# Termina OSAL shared sources
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/list/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/system/*.c)
# Implementation of the Termina OSAL for POSIX
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/posix/src/*.c)
# Implementation of the System API of the Termina OSAL for POSIX
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/posix/src/system/*.c)
# Platform-specific files for POSIX GCC
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/posix-gcc/src/*.c)

# Compilation flags

CFLAGS+=-O0 -g3 -Wall -D__TERMINA_NUMBER_OF_INTERRUPTS=0
