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
#
# The shared system sources are listed one by one instead of taken with a
# wildcard: this back end implements print and time, but not read, so
# shared/src/system/sys_read.c must stay out of the build.
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/system.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/sys_print.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/sys_time.c
# Implementation of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/*.c)
# Implementation of the System API of the Termina OSAL for RTEMS5
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems5/src/system/*.c)
# Platform-specific files for RTEMS5-LEON3-NEXYSA7
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/rtems5-leon3-nexysa7/src/*.c)

# Compilation flags

# The RCC headers are added with -isystem so that the compiler treats them as
# system headers and does not report diagnostics from them under
# -pedantic-errors and -Wextra. _DEFAULT_SOURCE keeps visible the POSIX and BSD
# declarations that newlib hides when compiling with -std=c11 and that the RTEMS
# headers need (for instance, struct bintime in rtems/confdefs.h). See
# shared/shared.mk.
CFLAGS+= -isystem /opt/rcc/sparc-gaisler-rtems5/leon3/lib/include -fmessage-length=0 -mcpu=leon3 -qbsp=leon3_sf -msoft-float -O0 -g3 -D_DEFAULT_SOURCE -D__TERMINA_NUMBER_OF_INTERRUPTS=16

# Static analysis platform (SPARC V8, 32 bits)

CPPCHECK_PLATFORM:=unix32
