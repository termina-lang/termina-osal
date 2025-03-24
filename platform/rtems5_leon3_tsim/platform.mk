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
# Implementation of the Termina OSAL for RTEMS5-LEON3-TSIM
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/rtems5_leon3_tsim/include

# Adding Termina OSAL source folders

# Termina OSAL shared sources
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/system/*.c)
# Implementation of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/*.c)
# Implementation of the System API of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/system/*.c)
# Platform-specific files for RTEMS5-LEON3-TSIM
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/rtems5_leon3_tsim/src/*.c)

# Compilation flags

CFLAGS+= -I/opt/rcc-1.3.2-gcc/sparc-gaisler-rtems5/leon3/lib/include -fmessage-length=0 -mcpu=leon3 -qbsp=leon3 -O2 -g3
