# Termina OSAL Makefile: settings shared by every platform
#
# Included at the end of the application Makefile and of the Makefiles of the
# validation suites, once the platform Makefile has set the compiler, the
# platform flags and CPPCHECK_PLATFORM, and the including Makefile has set
# TARGET_DIR_NAME, INCLUDE_DIRS and SRCS.

# Compilation flags common to all platforms

CFLAGS+=-std=c11 -pedantic-errors -Wall -Wextra -Wconversion -Wmissing-prototypes -Wshadow -Wstrict-prototypes -Wcast-qual -Wundef -Wvla -Wwrite-strings -Wdouble-promotion

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

CPPCHECK_INPUTS=$(filter -D%,$(CFLAGS)) $(addprefix -I,$(INCLUDE_DIRS)) $(SRCS)

.PHONY: cppcheck cppcheck-misra

cppcheck:
	@echo Running cppcheck
	@$(MKDIR) -p $(CPPCHECK_BUILD_DIR)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) --cppcheck-build-dir=$(CPPCHECK_BUILD_DIR) $(CPPCHECK_INPUTS)

cppcheck-misra:
	@echo Running cppcheck with the MISRA addon
	@$(MKDIR) -p $(CPPCHECK_MISRA_BUILD_DIR)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPPCHECK_MISRA_FLAGS) --cppcheck-build-dir=$(CPPCHECK_MISRA_BUILD_DIR) $(CPPCHECK_INPUTS)
