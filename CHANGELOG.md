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
