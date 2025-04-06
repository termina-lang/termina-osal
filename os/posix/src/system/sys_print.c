
#include <termina.h>

#include <termina/shared/system/sys_print.h>

#include <inttypes.h>

#include <stdio.h>

void SystemEntry__print(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    for (size_t i = 0; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE && str[i] != '\0'; i = i + 1) {

        putchar(str[i]);

    }

}

void SystemEntry__println(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    SystemEntry__print(str);
    putchar('\n');

}

void SystemEntry__print_char(const char c) {

    putchar(c);

}

void SystemEntry__println_char(const char c) {

    putchar(c);
    putchar('\n');

}

void SystemEntry__print_u8(const uint8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRIu8, value);
    } else {
        printf("0x%" PRIX8, value);
    }

}

void SystemEntry__println_u8(const uint8_t value, const SysPrintBase base) {

    SystemEntry__print_u8(value, base);
    putchar('\n');

}

void SystemEntry__print_u16(const uint16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRIu16, value);
    } else {
        printf("0x%" PRIX16, value);
    }

}

void SystemEntry__println_u16(const uint16_t value, const SysPrintBase base) {

    SystemEntry__print_u16(value, base);
    putchar('\n');

}

void SystemEntry__print_u32(const uint32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRIu32, value);
    } else {
        printf("0x%" PRIX32, value);
    }

}

void SystemEntry__println_u32(const uint32_t value, const SysPrintBase base) {

    SystemEntry__print_u32(value, base);
    putchar('\n');

}

void SystemEntry__print_u64(const uint64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRIu64, value);
    } else {
        printf("0x%" PRIX64, value);
    }

}

void SystemEntry__println_u64(const uint64_t value, const SysPrintBase base) {

    SystemEntry__print_u64(value, base);
    putchar('\n');

}

void SystemEntry__print_i8(const int8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRId8, value);
    } else {
        printf("0x%" PRIx8, value);
    }

}

void SystemEntry__println_i8(const int8_t value, const SysPrintBase base) {

    SystemEntry__print_i8(value, base);
    putchar('\n');

}

void SystemEntry__print_i16(const int16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRId16, value);
    } else {
        printf("0x%" PRIX16, value);
    }

}

void SystemEntry__println_i16(const int16_t value, const SysPrintBase base) {

    SystemEntry__print_i16(value, base);
    putchar('\n');

}

void SystemEntry__print_i32(const int32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRId32, value);
    } else {
        printf("0x%" PRIX32, value);
    }

}

void SystemEntry__println_i32(const int32_t value, const SysPrintBase base) {

    SystemEntry__print_i32(value, base);
    putchar('\n');

}

void SystemEntry__print_i64(const int64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%" PRId64, value);
    } else {
        printf("0x%" PRIX64, value);
    }

}

void SystemEntry__println_i64(const int64_t value, const SysPrintBase base) {

    SystemEntry__print_i64(value, base);
    putchar('\n');

}

void SystemEntry__print_usize(const size_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printf("%zu", value);
    } else {
        if (sizeof(size_t) <= 4) {
            printf("0x%08zx", value);
        } else {
            printf("0x%016zx", value);
        }

    }

}

void SystemEntry__println_usize(const size_t value, const SysPrintBase base) {

    SystemEntry__print_usize(value, base);
    putchar('\n');

}

