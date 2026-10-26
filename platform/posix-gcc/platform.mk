# Termina OSAL Makefile

CROSS=

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
# Test runtime, only in a test build (TERMINA_TEST=1 from the generated Makefile)
ifeq ($(TERMINA_TEST),1)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/shared/src/test/*.c)
OSAL_SRCS+=$(wildcard $(TERMINA_OSAL_DIR)/os/posix/src/test/*.c)
endif

# Compilation flags

# _DEFAULT_SOURCE keeps visible the POSIX and BSD declarations used by the POSIX
# back end (usleep, struct sigaction), which glibc hides when compiling with
# -std=c11 (see platform/common.mk).
CFLAGS+=-D_DEFAULT_SOURCE

# The GCC of some distributions, such as Ubuntu, makes the linker add a build
# ID, a hash of the whole binary that changes with its debugging information,
# so two builds of the same code would differ without it. The option is only
# passed when the target of the compiler does not contain "darwin" (findstring
# gives an empty string), since ld64 on Darwin does not take it.

ifeq ($(findstring darwin,$(shell $(CC) -dumpmachine)),)
LDFLAGS+=-Wl,--build-id=none
endif

# Static analysis platform (host)

CPPCHECK_PLATFORM:=unix64
