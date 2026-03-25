# Termina OSAL Makefile

CROSS:=/opt/rcc/bin/sparc-gaisler-rtems5-

CC:=$(CROSS)gcc

# Adding Termina OSAL header folders

# Main Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/api
# Shared Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/shared/include
# Implementation of the Termina OSAL for RTEMS5
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/os/rtems5/include
# Implementation of the Termina OSAL for RTEMS5-LEON3-NEXYSA7
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/rtems5-leon3-nexysa7/include

# Adding Termina OSAL source folders

# Termina OSAL shared sources
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/system.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/sys_print.c
# Implementation of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/*.c)
# Implementation of the System API of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/system/*.c)
# Platform-specific files for RTEMS5-LEON3-NEXYSA7
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/rtems5-leon3-nexysa7/src/*.c)

# Compilation flags

CFLAGS+= -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -fmessage-length=0 -mcpu=leon3 -qbsp=leon3_sf -msoft-float -O0 -g3 -D__TERMINA_NUMBER_OF_INTERRUPTS=16
