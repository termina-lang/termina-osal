# Termina OSAL Makefile: settings shared by every platform
#
# Included at the end of the application Makefile and of the Makefiles of the
# validation suites, once the platform Makefile has set the compiler, the
# platform flags and CPPCHECK_PLATFORM, and the including Makefile has set
# TARGET_DIR_NAME, INCLUDE_DIRS and SRCS. The application Makefile sets
# PROJECT_INCLUDE_DIRS as well, the directories of its own headers, which it
# compiles with -iquote.

# Compilation flags common to all platforms

CFLAGS+=-std=c11 -pedantic-errors -Wall -Wextra -Wconversion -Wmissing-prototypes -Wshadow -Wstrict-prototypes -Wcast-qual -Wundef -Wvla -Wwrite-strings -Wdouble-promotion -fno-common

# Test build
#
# TERMINA_TEST comes from the generated makefile of a test, and the platform
# makefile adds the sources of the test runtime with it.

ifeq ($(TERMINA_TEST),1)
CFLAGS+=-DTERMINA__TEST
endif

# Profile
#
# The release profile is built with -O2 -g, as the RCC manual and the board
# support package of the PYNQ do, and the debug one with -O0 -g3. The debugging
# information does not change the code, and keeps the delivered binary
# debuggable. TERMINA_PROFILE comes from the generated makefile, and a build
# made by hand without it, such as the validation suites, gets the flags of the
# debug profile.

ifeq ($(TERMINA_PROFILE),release)
CFLAGS+=-O2 -g
else
CFLAGS+=-O0 -g3
endif

# Unused sections
#
# Every function and every object goes in a section of its own, whatever the
# profile, and the link discards the sections nothing reaches. The link map,
# written next to the binary, lists the discarded ones. On Darwin the linker is
# ld64, which takes -dead_strip and -map instead.

CFLAGS+=-ffunction-sections -fdata-sections

ifneq ($(findstring darwin,$(shell $(CC) -dumpmachine)),)
LDFLAGS+=-Wl,-dead_strip -Wl,-map,$@.map
else
LDFLAGS+=-Wl,--gc-sections -Wl,-Map=$@.map
endif

# Extern C of the project
#
# The application Makefile links the objects of the extern C sources and the
# static libraries of the platform into a single relocatable object with
# $(call termina_extern_link,OUT,OBJS,LIBS,SYMBOLS). Only the extern functions
# (SYMBOLS) stay global in it, and tools/extern/link.sh checks it: no global
# defined both by a source and by a library, every extern function defined,
# nothing undefined outside the C library and libgcc, no constructors and no
# mutable state. The platform Makefile sets LD, OBJCOPY, NM and OBJDUMP, and
# TERMINA_EXTERN_LIBC when its link uses a C library other than libc.a.

TERMINA_EXTERN_LIBC?=libc.a

termina_extern_link=CC='$(CC)' CFLAGS='$(CFLAGS)' LD='$(LD)' OBJCOPY='$(OBJCOPY)' NM='$(NM)' OBJDUMP='$(OBJDUMP)' \
	LIBC='$(TERMINA_EXTERN_LIBC)' \
	sh $(TERMINA_OSAL_DIR)/tools/extern/link.sh '$(1)' '$(2)' '$(3)' '$(4)'

# Static analysis with Cppcheck
#
# Analyses the sources of the project (SRCS), not the OSAL, which is analysed in
# its own repository. Findings located in the OSAL headers are suppressed.
#
# The cppcheck-misra target runs the same analysis plus the MISRA addon, which
# checks the rules of MISRA C:2012; without a rule-texts file each finding
# names its rule only in the id (e.g., misra-c2012-11.5). The addon has no
# option to filter by category, so tools/cppcheck/misra.json suppresses the
# advisory rules by number and only the mandatory and required ones are
# reported. Each target keeps its own build directory, so that the results
# cached by one run are not reused by the other.

CPPCHECK:=cppcheck

CPPCHECK_BUILD_DIR:=$(TARGET_DIR_NAME)/cppcheck
CPPCHECK_MISRA_BUILD_DIR:=$(TARGET_DIR_NAME)/cppcheck-misra

# Exit code of cppcheck when it reports findings. By default the targets do
# not fail; set it to a non-zero value to make them fail (e.g., in CI).
CPPCHECK_ERROR_EXITCODE?=0

CPPCHECK_FLAGS:=--language=c --std=c11 --platform=$(CPPCHECK_PLATFORM) \
	--enable=warning,style,performance,portability \
	--check-level=exhaustive \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	'--suppress=*:$(TERMINA_OSAL_DIR)/*' \
	--error-exitcode=$(CPPCHECK_ERROR_EXITCODE)

CPPCHECK_MISRA_FLAGS:=--addon=$(TERMINA_OSAL_DIR)/tools/cppcheck/misra.json

CPPCHECK_INPUTS=$(filter -D%,$(CFLAGS)) $(addprefix -I,$(PROJECT_INCLUDE_DIRS)) $(addprefix -I,$(INCLUDE_DIRS)) $(SRCS)

.PHONY: cppcheck cppcheck-misra

cppcheck:
	@echo Running cppcheck
	@$(MKDIR) -p $(CPPCHECK_BUILD_DIR)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --cppcheck-build-dir=$(CPPCHECK_BUILD_DIR) $(CPPCHECK_INPUTS)

cppcheck-misra:
	@echo Running cppcheck with the MISRA addon
	@$(MKDIR) -p $(CPPCHECK_MISRA_BUILD_DIR)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_MISRA_FLAGS) --cppcheck-build-dir=$(CPPCHECK_MISRA_BUILD_DIR) $(CPPCHECK_INPUTS)
