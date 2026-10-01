# Termina OSAL Makefile

# Installation prefix of the RTEMS 6 tools and board support packages. A build
# outside the development container may override it.
RTEMS6_PREFIX?=/opt/rtems/6

CROSS:=$(RTEMS6_PREFIX)/bin/arm-rtems6-

CC:=$(CROSS)gcc

# Directory of the board support package of the PYNQ-Z2
RTEMS6_BSP_DIR:=$(RTEMS6_PREFIX)/arm-rtems6/xilinx_zynq_pynq/lib

# Adding Termina OSAL header folders

# Main Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/api
# Shared Termina OSAL API
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/shared/include
# Implementation of the Termina OSAL for RTEMS
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/os/rtems/include
# Implementation of the Termina OSAL for RTEMS6-ZYNQ7000-PYNQZ2
INCLUDE_DIRS+=$(TERMINA_OSAL_DIR)/platform/rtems6-zynq7000-pynqz2/include

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
# Implementation of the System API of the Termina OSAL for RTEMS
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/rtems/src/system/*.c)
# Platform-specific files for RTEMS6-ZYNQ7000-PYNQZ2
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/platform/rtems6-zynq7000-pynqz2/src/*.c)

# Compilation flags

# The flags of the application binary interface are the ones the board support
# package was built with, as its pkg-config file gives them
# (arm-rtems6-xilinx_zynq_pynq.pc).
ABI_FLAGS:=-march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9

# The headers of the board support package are added with -isystem so that the
# compiler treats them as system headers and does not report diagnostics from
# them under -pedantic-errors and -Wextra. _DEFAULT_SOURCE keeps visible the
# POSIX and BSD declarations that newlib hides when compiling with -std=c11 and
# that the RTEMS headers need (for instance, struct bintime in
# rtems/confdefs.h).
CFLAGS+= $(ABI_FLAGS) -isystem $(RTEMS6_BSP_DIR)/include -fmessage-length=0 -D_DEFAULT_SOURCE

# Linking flags
LDFLAGS+= -B$(RTEMS6_BSP_DIR) -qrtems -Wl,--gc-sections

# The board support package is built with -O2 -g, and the release build follows
# it. TERMINA_PROFILE comes from the generated makefile, and a build made by
# hand without it gets the flags of the debug profile.
ifeq ($(TERMINA_PROFILE),release)
CFLAGS+= -O2 -g
else
CFLAGS+= -O0 -g3
endif

# Static analysis and additional warnings
CFLAGS+= -fanalyzer -Wcast-align=strict -Wlogical-op -Wduplicated-cond -Wduplicated-branches

# Static analysis platform (ARMv7-A, 32 bits)

CPPCHECK_PLATFORM:=arm32-wchar_t4
