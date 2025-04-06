
#include <termina.h>

#include <termina/shared/system/sys_print.h>

#include <inttypes.h>

#include <rtems/bspIo.h>

void System__print(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    for (size_t i = 0; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE && str[i] != '\0'; i = i + 1) {

        rtems_putc(str[i]);

    }

}

void System__println(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    System__print(str);
    rtems_putc('\n');

}

void System__print_char(const char c) {

    rtems_putc(c);

}

void System__println_char(const char c) {

    rtems_putc(c);
    rtems_putc('\n');

}

void System__print_u8(const uint8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRIu8, value);
    } else {
        printk("0x%02x", value);
    }

}

void System__println_u8(const uint8_t value, const SysPrintBase base) {

    System__print_u8(value, base);
    rtems_putc('\n');

}

void System__print_u16(const uint16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%u", value);
    } else {
        printk("0x%04x", value);
    }

}

void System__println_u16(const uint16_t value, const SysPrintBase base) {

    System__print_u16(value, base);
    rtems_putc('\n');

}

void System__print_u32(const uint32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%u", value);
    } else {
        printk("0x%08x", value);
    }

}

void System__println_u32(const uint32_t value, const SysPrintBase base) {

    System__print_u32(value, base);
    rtems_putc('\n');

}

void System__print_u64(const uint64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%llu", value);
    } else {
        printk("0x%016llx", value);
    }

}

void System__println_u64(const uint64_t value, const SysPrintBase base) {

    System__print_u64(value, base);
    rtems_putc('\n');

}

void System__print_i8(const int8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId8, value);
    } else {
        printk("0x$" PRIx8, value);
    }

}

void System__println_i8(const int8_t value, const SysPrintBase base) {

    System__print_i8(value, base);
    rtems_putc('\n');

}

void System__print_i16(const int16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId16, value);
    } else {
        printk("0x%" PRIX16, value);
    }

}

void System__println_i16(const int16_t value, const SysPrintBase base) {

    System__print_i16(value, base);
    rtems_putc('\n');

}

void System__print_i32(const int32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId32, value);
    } else {
        printk("0x%" PRIX32, value);
    }

}

void System__println_i32(const int32_t value, const SysPrintBase base) {

    System__print_i32(value, base);
    rtems_putc('\n');

}

void System__print_i64(const int64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId64, value);
    } else {
        printk("0x%" PRIX64, value);
    }

}

void System__println_i64(const int64_t value, const SysPrintBase base) {

    System__print_i64(value, base);
    rtems_putc('\n');

}

void System__print_usize(const size_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%zu", value);
    } else {
        if (sizeof(size_t) <= 4) {
            printk("0x%08zx", value);
        } else {
            printk("0x%016zx", value);
        }

    }

}

void System__println_usize(const size_t value, const SysPrintBase base) {

    System__print_usize(value, base);
    rtems_putc('\n');

}

