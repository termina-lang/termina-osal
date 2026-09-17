# Reads the build settings of a platform out of the OSAL, so that the probe
# compiles with the same compiler, include path and flags as the generated code
# does. The flags decide what the probe sees: posix-gcc and rtems5 pass
# -D_DEFAULT_SOURCE, which is what makes <string.h> pull in <strings.h> and
# declare index(), while freertos10 does not.
#
#   make -f probe.mk PLATFORM=posix-gcc print-CC
#   make -f probe.mk PLATFORM=posix-gcc print-INCLUDE_DIRS
#   make -f probe.mk PLATFORM=posix-gcc print-CFLAGS

TERMINA_OSAL_DIR?=/opt/termina-osal

# | The two of them, and in this order, which is how the Makefile that a project
# generates puts its own flags together. The standard comes from shared.mk, and
# it decides as much as the defines do: under -std=c11 a library hides the names
# of POSIX that it hands out under -std=gnu11.
include $(TERMINA_OSAL_DIR)/platform/$(PLATFORM)/platform.mk
include $(TERMINA_OSAL_DIR)/shared/shared.mk

print-%: ; @echo $($*)
