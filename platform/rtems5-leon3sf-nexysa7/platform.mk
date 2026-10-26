# Termina OSAL Makefile

# Installation folder of the RCC, from which the compiler and the RTEMS
# headers are taken. The environment or the command line of make may change it.
TERMINA_RCC_DIR?=/opt/rcc

CROSS=$(TERMINA_RCC_DIR)/bin/sparc-gaisler-rtems5-

CC:=$(CROSS)gcc
LD:=$(CROSS)ld
OBJCOPY:=$(CROSS)objcopy
NM:=$(CROSS)nm
OBJDUMP:=$(CROSS)objdump

# Adding Termina OSAL header folders

# Main Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/api
# Shared Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/shared/include
# Implementation of the Termina OSAL for RTEMS
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/os/rtems/include
# Implementation of the Termina OSAL for RTEMS5-LEON3SF-NEXYSA7
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/rtems5-leon3sf-nexysa7/include

# Adding Termina OSAL source folders

# Termina OSAL shared sources
#
# The shared system sources are listed one by one instead of taken with a
# wildcard: this back end implements time, but neither print nor read, so
# shared/src/system/sys_print.c and shared/src/system/sys_read.c must stay out
# of the build.
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/*.c)
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/system.c
OSAL_SRCS+=$(TERMINA_OSAL_DIR)/shared/src/system/sys_time.c
# Implementation of the Termina OSAL for RTEMS
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems/src/*.c)
# Platform-specific files for RTEMS5-LEON3SF-NEXYSA7
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/rtems5-leon3sf-nexysa7/src/*.c)
# Test runtime, only in a test build (TERMINA_TEST=1 from the generated Makefile)
ifeq ($(TERMINA_TEST),1)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/test/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems/src/test/*.c)
endif

# Compilation flags

# The RCC headers are added with -isystem so that the compiler treats them as
# system headers and does not report diagnostics from them under
# -pedantic-errors and -Wextra. _DEFAULT_SOURCE keeps visible the POSIX and BSD
# declarations that newlib hides when compiling with -std=c11 and that the RTEMS
# headers need (for instance, struct bintime in rtems/confdefs.h).
CFLAGS+= -isystem $(TERMINA_RCC_DIR)/sparc-gaisler-rtems5/leon3/lib/include -fmessage-length=0 -mcpu=leon3 -qbsp=leon3_sf -msoft-float -D_DEFAULT_SOURCE

# Static analysis and additional warnings
CFLAGS+= -fanalyzer -Wcast-align=strict -Wlogical-op -Wduplicated-cond -Wduplicated-branches

# Static analysis platform (SPARC V8, 32 bits)

CPPCHECK_PLATFORM:=unix32
