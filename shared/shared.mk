# Termina OSAL Makefile: settings shared by every platform
#
# Included at the end of the application Makefile and of the Makefiles of the
# validation suites, once the platform Makefile has set the compiler, the
# platform flags and CPPCHECK_PLATFORM, and the including Makefile has set
# TARGET_DIR_NAME, INCLUDE_DIRS and SRCS.

# Compilation flags common to all platforms

CFLAGS+=-std=c11 -pedantic-errors -Wall -Wextra

# Static analysis with Cppcheck
#
# Analyses the sources of the project (SRCS), not the OSAL, which is analysed in
# its own repository. Findings located in the OSAL headers are suppressed.

CPPCHECK:=cppcheck

CPPCHECK_BUILD_DIR:=$(TARGET_DIR_NAME)/cppcheck

# Exit code of cppcheck when it reports findings. By default the target does
# not fail; set it to a non-zero value to make it fail (e.g., in CI).
CPPCHECK_ERROR_EXITCODE?=0

# Termina requires every variable to be initialized when it is declared, also
# when all the branches that follow assign it, so an initial value overwritten
# before it is read is expected and not reported (redundantInitialization,
# unreadVariable). The transpiler rejects assigned values that are never read.
CPPCHECK_FLAGS:=--language=c --std=c11 --platform=$(CPPCHECK_PLATFORM) \
	--enable=warning,style,performance,portability \
	--check-level=exhaustive \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=redundantInitialization \
	--suppress=unreadVariable \
	'--suppress=*:$(TERMINA_OSAL_DIR)/*' \
	--cppcheck-build-dir=$(CPPCHECK_BUILD_DIR) \
	--error-exitcode=$(CPPCHECK_ERROR_EXITCODE)

.PHONY: cppcheck

cppcheck:
	@echo Running cppcheck
	@$(MKDIR) -p $(CPPCHECK_BUILD_DIR)
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(filter -D%,$(CFLAGS)) $(addprefix -I,$(INCLUDE_DIRS)) $(SRCS)
