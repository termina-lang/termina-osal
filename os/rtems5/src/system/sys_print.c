
#include <termina.h>

#include <termina/shared/system/sys_print.h>

#include <inttypes.h>

#include <rtems/bspIo.h>

void __termina_sys_print__print(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    for (size_t i = 0; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE && str[i] != '\0'; i = i + 1) {

        rtems_putc(str[i]);

    }

}

void __termina_sys_print__println(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    __termina_sys_print__print(str);
    rtems_putc('\n');

}

void __termina_sys_print__print_char(const char c) {

    rtems_putc(c);

}

void __termina_sys_print__println_char(const char c) {

    rtems_putc(c);
    rtems_putc('\n');

}

void __termina_sys_print__print_u8(const uint8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRIu8, value);
    } else {
        printk("0x%02x", value);
    }

}

void __termina_sys_print__println_u8(const uint8_t value, const SysPrintBase base) {

    __termina_sys_print__print_u8(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_u16(const uint16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%u", value);
    } else {
        printk("0x%04x", value);
    }

}

void __termina_sys_print__println_u16(const uint16_t value, const SysPrintBase base) {

    __termina_sys_print__print_u16(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_u32(const uint32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%u", value);
    } else {
        printk("0x%08x", value);
    }

}

void __termina_sys_print__println_u32(const uint32_t value, const SysPrintBase base) {

    __termina_sys_print__print_u32(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_u64(const uint64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%llu", value);
    } else {
        printk("0x%016llx", value);
    }

}

void __termina_sys_print__println_u64(const uint64_t value, const SysPrintBase base) {

    __termina_sys_print__print_u64(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_i8(const int8_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId8, value);
    } else {
        printk("0x$" PRIx8, value);
    }

}

void __termina_sys_print__println_i8(const int8_t value, const SysPrintBase base) {

    __termina_sys_print__print_i8(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_i16(const int16_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId16, value);
    } else {
        printk("0x%" PRIX16, value);
    }

}

void __termina_sys_print__println_i16(const int16_t value, const SysPrintBase base) {

    __termina_sys_print__print_i16(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_i32(const int32_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId32, value);
    } else {
        printk("0x%" PRIX32, value);
    }

}

void __termina_sys_print__println_i32(const int32_t value, const SysPrintBase base) {

    __termina_sys_print__print_i32(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_i64(const int64_t value, const SysPrintBase base) {

    if (base.__variant == SysPrintBase__Decimal) {
        printk("%" PRId64, value);
    } else {
        printk("0x%" PRIX64, value);
    }

}

void __termina_sys_print__println_i64(const int64_t value, const SysPrintBase base) {

    __termina_sys_print__print_i64(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__print_usize(const size_t value, const SysPrintBase base) {

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

void __termina_sys_print__println_usize(const size_t value, const SysPrintBase base) {

    __termina_sys_print__print_usize(value, base);
    rtems_putc('\n');

}

void __termina_sys_print__init_mutex(__termina_id_t mutex_id) {

    __termina_sys_print.mutex_id = mutex_id;
    __termina_sys_print.print = __termina_sys_print__print_mutex;
    __termina_sys_print.println = __termina_sys_print__println_mutex;

    __termina_sys_print.print_char = __termina_sys_print__print_char_mutex;
    __termina_sys_print.println_char = __termina_sys_print__println_char_mutex;

    __termina_sys_print.print_u8 = __termina_sys_print__print_u8_mutex;
    __termina_sys_print.println_u8 = __termina_sys_print__println_u8_mutex;

    __termina_sys_print.print_u16 = __termina_sys_print__print_u16_mutex;
    __termina_sys_print.println_u16 = __termina_sys_print__println_u16_mutex;

    __termina_sys_print.print_u32 = __termina_sys_print__print_u32_mutex;
    __termina_sys_print.println_u32 = __termina_sys_print__println_u32_mutex;

    __termina_sys_print.print_u64 = __termina_sys_print__print_u64_mutex;
    __termina_sys_print.println_u64 = __termina_sys_print__println_u64_mutex;

    __termina_sys_print.print_i8 = __termina_sys_print__print_i8_mutex;
    __termina_sys_print.println_i8 = __termina_sys_print__println_i8_mutex;

    __termina_sys_print.print_i16 = __termina_sys_print__print_i16_mutex;
    __termina_sys_print.println_i16 = __termina_sys_print__println_i16_mutex;

    __termina_sys_print.print_i32 = __termina_sys_print__print_i32_mutex;
    __termina_sys_print.println_i32 = __termina_sys_print__println_i32_mutex;

    __termina_sys_print.print_i64 = __termina_sys_print__print_i64_mutex;
    __termina_sys_print.println_i64 = __termina_sys_print__println_i64_mutex;

    __termina_sys_print.print_usize = __termina_sys_print__print_usize_mutex;
    __termina_sys_print.println_usize = __termina_sys_print__println_usize_mutex;

    return;

}

void __termina_sys_print__init_task_lock() {

    __termina_sys_print.print = __termina_sys_print__print_task_lock;
    __termina_sys_print.println = __termina_sys_print__println_task_lock;

    __termina_sys_print.print_char = __termina_sys_print__print_char_task_lock;
    __termina_sys_print.println_char = __termina_sys_print__println_char_task_lock;

    __termina_sys_print.print_u8 = __termina_sys_print__print_u8_task_lock;
    __termina_sys_print.println_u8 = __termina_sys_print__println_u8_task_lock;

    __termina_sys_print.print_u16 = __termina_sys_print__print_u16_task_lock;
    __termina_sys_print.println_u16 = __termina_sys_print__println_u16_task_lock;

    __termina_sys_print.print_u32 = __termina_sys_print__print_u32_task_lock;
    __termina_sys_print.println_u32 = __termina_sys_print__println_u32_task_lock;

    __termina_sys_print.print_u64 = __termina_sys_print__print_u64_task_lock;
    __termina_sys_print.println_u64 = __termina_sys_print__println_u64_task_lock;

    __termina_sys_print.print_i8 = __termina_sys_print__print_i8_task_lock;
    __termina_sys_print.println_i8 = __termina_sys_print__println_i8_task_lock;

    __termina_sys_print.print_i16 = __termina_sys_print__print_i16_task_lock;
    __termina_sys_print.println_i16 = __termina_sys_print__println_i16_task_lock;

    __termina_sys_print.print_i32 = __termina_sys_print__print_i32_task_lock;
    __termina_sys_print.println_i32 = __termina_sys_print__println_i32_task_lock;

    __termina_sys_print.print_i64 = __termina_sys_print__print_i64_task_lock;
    __termina_sys_print.println_i64 = __termina_sys_print__println_i64_task_lock;

    __termina_sys_print.print_usize = __termina_sys_print__print_usize_task_lock;
    __termina_sys_print.println_usize = __termina_sys_print__println_usize_task_lock;

    return;

}

void __termina_sys_print__init_event_lock() {

    __termina_sys_print.print = __termina_sys_print__print_event_lock;
    __termina_sys_print.println = __termina_sys_print__println_event_lock;

    __termina_sys_print.print_char = __termina_sys_print__print_char_event_lock;
    __termina_sys_print.println_char = __termina_sys_print__println_char_event_lock;

    __termina_sys_print.print_u8 = __termina_sys_print__print_u8_event_lock;
    __termina_sys_print.println_u8 = __termina_sys_print__println_u8_event_lock;

    __termina_sys_print.print_u16 = __termina_sys_print__print_u16_event_lock;
    __termina_sys_print.println_u16 = __termina_sys_print__println_u16_event_lock;

    __termina_sys_print.print_u32 = __termina_sys_print__print_u32_event_lock;
    __termina_sys_print.println_u32 = __termina_sys_print__println_u32_event_lock;

    __termina_sys_print.print_u64 = __termina_sys_print__print_u64_event_lock;
    __termina_sys_print.println_u64 = __termina_sys_print__println_u64_event_lock;
    
    __termina_sys_print.print_i8 = __termina_sys_print__print_i8_event_lock;
    __termina_sys_print.println_i8 = __termina_sys_print__println_i8_event_lock;

    __termina_sys_print.print_i16 = __termina_sys_print__print_i16_event_lock;
    __termina_sys_print.println_i16 = __termina_sys_print__println_i16_event_lock;

    __termina_sys_print.print_i32 = __termina_sys_print__print_i32_event_lock;
    __termina_sys_print.println_i32 = __termina_sys_print__println_i32_event_lock;

    __termina_sys_print.print_i64 = __termina_sys_print__print_i64_event_lock;
    __termina_sys_print.println_i64 = __termina_sys_print__println_i64_event_lock;

    __termina_sys_print.print_usize = __termina_sys_print__print_usize_event_lock;
    __termina_sys_print.println_usize = __termina_sys_print__println_usize_event_lock;

    return;

}