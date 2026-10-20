# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)
with pre-1.0 semantics: while in `0.x`, minor bumps may include breaking changes.

The OSAL version is kept in lockstep at the `MAJOR.MINOR` level with the
[Termina transpiler](https://github.com/termina-lang/termina): the same
`v0.X.Y` major and minor on both repositories guarantees compatibility.
Patch versions on either side are interchangeable.

## [Unreleased]

### Added

- Deques in `termina/deque.h`: `termina__deque_t`, a queue of boxes over an
  array that the application declares, with `termina__deque__init`,
  `termina__deque__take`, `termina__deque__put`, `termina__deque__put_front`,
  `termina__deque__try_put` and `termina__deque__replace`. A put into a full
  deque raises `ERuntimeFailure` with the new operation
  `termina__runtime_operation__deque_put` and the error code
  `termina__error__deque_full`.

### Removed

- Actions return nothing, so the action types of `termina/emitter.h` return
  `void` and the back-ends call the action of a timer, an interrupt or
  `system_init` without checking a status. `EActionFailure` leaves
  `Exception`, together with `ExceptSource`, `termina__except__action_failure`
  and `termina__shared__except__handler_failure`. `Status__i32` leaves the
  prelude: the transpiler generates it in the application that uses it. This
  release needs a matching transpiler.

## [0.6.0] - 2026-10-15

### Added

- `platform/common.mk`, included by the Makefile the transpiler generates: C11
  strict flags on every platform, a `cppcheck` target, and a `cppcheck-misra`
  target that runs the MISRA addon with the mandatory and required rules. The
  exit code of cppcheck is set with `CPPCHECK_ERROR_EXITCODE` (0 by default).
- `termina__system_init__dispatch`, which dispatches the initial event from the
  runtime.
- Run-time bound check of the shift amount.
- Run-time checks of signed arithmetic and of divisors in `termina/check.h`:
  `termina__check__{add,sub,mul,div,mod}_{i8,i16,i32,i64}`, which carry out
  the operation once they have checked that its result is representable, and
  `termina__check__divisor_{u8,u16,u32,u64,usize}` for unsigned divisions and
  remainders. They raise the new exceptions `EArithmeticOverflow` and
  `EDivisionByZero`, and do not depend on the width of `int`.
- In the `debug` profile, the runtime stops at a breakpoint before a reset; on
  `rtems5-leon3sf-nexysa7` the optimization level follows the profile.
- `tools/reserved`, which generates the lists of names that each platform
  reserves, read by the transpiler.
- `termina/app.h` declares the global initialization function, and the common
  types include `<stdbool.h>`.
- The GCC static analyzer runs on `rtems5-leon3sf-nexysa7`.
- `ERuntimeFailure`, raised with the operation and the error code when the
  runtime fails to take or give back a mutex, to arm a periodic timer or to make
  a task ready to run. These failures were ignored before.
- The `rtems6-zynq7000-pynqz2` platform: RTEMS 6 on the Zynq-7000 of the
  PYNQ-Z2 board, built with the `arm-rtems6` tools and the `xilinx_zynq_pynq`
  board support package, installed under `RTEMS6_PREFIX` (`/opt/rtems/6` by
  default).
- `vendor/FreeRTOS-Kernel`, the files of the FreeRTOS kernel that the platforms
  build, as the tag of `FreeRTOS/FreeRTOS-Kernel` holds them, and
  `vendor/FreeRTOS-Kernel.lock`, which records the tag, the commit and the hash
  of each file. `tools/vendor/vendor.sh` fetches the copy and verifies it.
- The `EProcessorFault` and `EKernelFailure` variants of `Exception`, raised
  through `termina__except__processor_fault` and
  `termina__except__kernel_failure`. Faults of the processor and fatal errors
  of the operating system now reach the `system_except` handler before the
  reboot:
  - `rtems`: a fatal extension of RTEMS. A processor exception goes through
    `termina__rtems__platform__processor_fault`, which each RTEMS platform
    implements from the exception frame; any other source but a shutdown
    raises `EKernelFailure`.
  - `freertos10-stm32l432-nucleol432kc`: the HardFault entry of the vector
    table, with `CFSR` and `MMFAR` or `BFAR`. `configASSERT` raises
    `EKernelFailure`.
  - `posix`: `SIGSEGV`, `SIGBUS`, `SIGFPE` and `SIGILL`.
- The `EStackOverflow` variant of `Exception`, raised through
  `termina__except__stack_overflow` with the identifier of the task whose stack
  overflowed, or `TERMINA__ID__INVALID` when the stack is not of a task of the
  application. On RTEMS 6 the stack checker is enabled and the OSAL is its
  reporter; on FreeRTOS `vApplicationStackOverflowHook` raises it
  (`configCHECK_FOR_STACK_OVERFLOW` 1). Both find the task in the task table
  of the back-end.
- `termina__exec__handover`, which the code generated for a call to an
  `extern noreturn` function calls first. It leaves nothing else able to run
  or interrupt, as the fatal path does.
- `termina_extern_link` in `common.mk`, which links the objects of the extern C
  sources of a project and the static libraries of the platform into one
  relocatable object with `tools/extern/link.sh`. Only the extern functions
  stay global, and the script checks that no global is defined twice, that
  every extern function is defined, that nothing is undefined outside the C
  library and `libgcc`, and that there are no constructors or mutable state.
  Each platform sets `LD`, `OBJCOPY`, `NM` and `OBJDUMP`. The extern C is
  compiled with `-fno-common`.
- Error codes `termina__error__invalid_block` (210) and
  `termina__error__no_handler` (211), and runtime operations `pool_free` (4),
  `task_dispatch` (5) and `irq_dispatch` (6).

### Changed

- **BREAKING**: the API, its macros and the internals of the back-ends move to
  the `termina` namespace (`termina__<module>__<name>`, `TERMINA__*`), together
  with the builtin types, struct fields and parameters shared with the generated
  code. Requires `termina v0.6.x`.
- **BREAKING**: the mutex takes its locking protocol as a `MutexProtocol` tagged
  value.
- **BREAKING**: `shared/shared.mk` moves to `platform/common.mk`.
- **BREAKING**: the functions of the runtime return a `termina__error_code_t`.
  The initialization of the application returns the function whose
  initialization failed, and an operation that fails while the application runs
  returns its cause, the same on every operating system, which the exception it
  raises carries.
- **BREAKING**: `termina__pool__area_length` gives the length of the memory
  area of a pool in elements of `max_align_t` and replaces
  `termina__pool__size`.
- **BREAKING**: `termina__task_prio_t` is a `uint32_t`. Application tasks take
  priorities from `TERMINA__TASK__MAXIMUM_PRIORITY` (1) to
  `TERMINA__TASK__MINIMUM_PRIORITY` (254), and `TERMINA__TASK__IDLE_PRIORITY`
  (255) is the one of the idle task. The FreeRTOS timer daemon runs at 0, which
  RTEMS does not accept for an application task.
- The `cppcheck` targets also take the header directories of the project from
  `PROJECT_INCLUDE_DIRS`, which the Makefile generated by `termina v0.6.x`
  compiles with `-iquote`.
- The size of the interrupt table comes from the generated `config.h`.
- The system primitives are split into `sys_print`, `sys_read` and `sys_time`,
  and every exception is raised through one path in the shared layer.
- The lock type is unsigned.
- **BREAKING**: `os/rtems5` becomes `os/rtems`, shared by the RTEMS 5 and
  RTEMS 6 platforms, with its header `termina/os/rtems/name.h`. The `Init` task
  moves from the platform to `os/rtems/src/main.c`, and the reboot from
  `os/rtems` to the platform.
- **BREAKING**: the RTEMS back-end provides no console: `rtems5-leon3sf-nexysa7`
  builds the time procedures of the system entry only, as the FreeRTOS back-end
  does.
- **BREAKING**: `freertos10-stm32l432xx` is renamed `freertos10-stm32l432-nucleol432kc`.
- **BREAKING**: `rtems5-leon3-nexysa7` is renamed `rtems5-leon3sf-nexysa7`. The
  platform compiles for soft-float, and in Gaisler's naming `leon3` is the
  board support package with a floating-point unit.
- `termina__os__except__enter` becomes `termina__os__exec__quiesce`, in the
  `exec.c` of each back-end.
- **BREAKING**: the action of the `system_except` handler receives the event as
  its first parameter, as the actions of the other emitters do, and the handler
  is registered through a connection, like the one of `system_init`.
- The RTEMS back-end installs an interrupt with
  `rtems_interrupt_handler_install`, which takes the vector number of the board
  support package, instead of `set_vector`, which only the SPARC ones declare. An
  installation that RTEMS rejects fails with `termina__error__os_failure`.
- The FreeRTOS kernel moves from V10.3.1 to V10.6.2 and comes unchanged from its
  repository. `FreeRTOSConfig.h` sets `configUSE_PORT_OPTIMISED_TASK_SELECTION`
  to 0, which the previous copy set inside `portmacro.h`.
- `termina__resource__lock` and `termina__resource__unlock` take the lock type
  as read only, so a procedure that takes `&self` can lock its resource.
- `termina__exec__reboot` no longer calls `rtems_shutdown_executive`, which ran
  the fatal extensions and printed through the console of the board support
  package. `rtems6-zynq7000-pynqz2` resets the processing system through
  `PSS_RST_CTRL` of the SLCR. `rtems5-leon3sf-nexysa7` stops the processor in
  error mode, since the board has no watchdog wired to its reset.

### Fixed

- `termina__pool__free` takes the lock of the pool, as `termina__pool__alloc`
  does. It updated the list of free blocks without it, so an allocation that
  preempted or interrupted it could corrupt the list.
- Every declaration names and qualifies its parameters as its definition does
  (the mutex, `delay_in`, interrupt, pool, task, message queue and character
  print entries differed), and the entries that raise an exception, which never
  return, are declared `_Noreturn`.
- `posix`: the thread that turns the standard input into the keyboard
  interrupt waits again when a signal interrupts it, and when the standard
  input is closed with nothing left to read it prints a warning and stops.
  It used to stop silently on any of them, and to fire the interrupt on every
  tick once a pipe was closed on systems that report it as readable.
- `posix-gcc` line-buffers standard output.
- `posix`: a queued message checks its data buffer, not the item.
- `rtems5-leon3sf-nexysa7` builds with the C11 strict flags and compiles the
  shared `sys_time` source; `freertos10-stm32l432-nucleol432kc` builds the
  shared system sources.
- `tools/reserved` takes the name of a function from its own declarator. A
  function with a parameter that is a pointer to a function was listed under
  the return type of that parameter.
- The blocks of a pool are aligned to `max_align_t`. `termina__pool__init`
  rejects a memory area that is not so aligned or does not hold a single block,
  and `termina__pool__free` takes back only the address of a block.
- A send through an out port raises `EMsgQueueSendError` when the message does
  not reach the queue of the channel or the event does not reach the queue of
  the task. Periodic timers and interrupts connected to a task deliver through
  the same path and raise the same exception.
- The action of a handler connected to a periodic timer or an interrupt that
  returns a failure raises `EActionFailure`, so the `system_except` handler runs
  before the reboot.
- The action connected to a periodic timer receives the time at which the timer
  was due. On `posix`, the next expiry is one period after that time, where it
  used to drift by the tick that served the timer.
- Every platform reboots when the initialization of the application fails,
  instead of starting the scheduler with part of the application initialized.
- `rtems5`: a periodic timer due in less than a tick, or already due, is armed
  for the next tick. It used to be armed for zero ticks, which RTEMS rejects,
  and the failure raised `ERuntimeFailure`. The interval up to the next expiry
  is rounded up, so the timer no longer fires a tick early.
- `freertos10`: the uptime, and the time that a periodic timer passes to its
  action, count the times the 32-bit tick count of the kernel wraps around, so
  they keep increasing after 2^32 ticks (49.7 days at a tick of 1 ms).
- `freertos10`: the initialization of a periodic timer that the kernel cannot
  create fails with `termina__error__os_failure`, where it used to succeed.
- `freertos10`: locking a mutex raises the task to the priority of the ceiling,
  and unlocking it returns an error when the caller is not the owner.
- `freertos10`: a send to a full queue fails, as on the other back-ends, instead
  of waiting for room.
- `posix`: in the `debug` profile the runtime stops at `SIGTRAP`, which it used
  to keep blocked, also when the initialization of the application fails.
- `posix`: `SIGTERM`, `SIGSEGV`, `SIGBUS`, `SIGFPE` and `SIGILL` stay unblocked.
- `termina__pool__free` raises `ERuntimeFailure` with operation `pool_free`
  when the address is not the start of a block of the pool or the pool is not
  valid. It returned without freeing anything.
- `freertos10`: an interrupt with no handler raises `ERuntimeFailure` with
  operation `irq_dispatch`, instead of rebooting without calling the
  `system_except` handler.

## [0.5.0] - 2026-06-19

### Changed

- **BREAKING**: `SystemEntry__print`, `SystemEntry__println` and
  `SystemEntry__read` no longer take a `size` argument. The buffer length is
  fixed by the `__TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE` and
  `__TERMINA_SYS_READ_INPUT_BUFFER_SIZE` macros, taken from the project's
  generated `config.h`; `sys_print.h` and `sys_read.h` fall back to 256 if the
  macros are not defined. Requires `termina v0.5.x`.


## [0.4.0] - 2026-06-18

### Added

- Runtime support for the `f32`/`f64` floating-point types: `float32_t` and
  `float64_t` typedefs in `api/termina/float.h` (mapped to `float`/`double`
  with static IEEE-754 binary32/binary64 checks) and the Prelude bit
  reinterpretation functions `f32_to_bits`/`f32_from_bits` and the `f64`
  variants. `float.h` is included from `termina.h`.
- `print_f32`/`println_f32`/`print_f64`/`println_f64` in the `SysPrint`
  interface, implemented for POSIX (`printf "%g"`) and RTEMS5 (`snprintf "%g"`
  plus `printk`, since `printk` has no floating-point conversions).

### Changed

- Bumped minor to `v0.4.0` to track transpiler `v0.4.0` (lockstep). The float
  runtime above is required by code generated by the new transpiler.


## [0.3.1] - 2026-05-25

### Fixed

- `platform/rtems5-leon3-nexysa7/platform.mk` no longer hardcodes the
  versioned RCC install path (`/opt/rcc-1.3.2-gcc/...`) for the BSP
  include directory; it now consistently uses the `/opt/rcc/` symlink,
  matching the `CROSS` prefix already defined at the top of the file.
  This makes the OSAL resilient to RCC version bumps inside the
  development container.

## [0.3.0] - 2026-05-25

### Added

- Initial release under the formal versioning policy, aligned with the
  Termina transpiler `v0.3.0`. Earlier history is preserved in `git log`
  but not catalogued here.
