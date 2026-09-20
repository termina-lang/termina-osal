
#include <termina.h>
#include <termina/shared/system/sys_print.h>

void SystemEntry__print(const termina__event_t * const termina__ev,
                        const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print(str);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println(const termina__event_t * const termina__ev, 
                          const char str[TERMINA__SYS_PRINT__OUTPUT_BUFFER_SIZE]) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println(str);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_char(const termina__event_t * const termina__ev, 
                             const char c) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_char(c);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);
}

void SystemEntry__println_char(const termina__event_t * const termina__ev, 
                               const char c) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_char(c);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_u8(const termina__event_t * const termina__ev, 
                           const uint8_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_u8(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_u8(const termina__event_t * const termina__ev, 
                             const uint8_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_u8(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_u16(const termina__event_t * const termina__ev, 
                            const uint16_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_u16(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_u16(const termina__event_t * const termina__ev, 
                              const uint16_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_u16(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_u32(const termina__event_t * const termina__ev, 
                            const uint32_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_u32(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_u32(const termina__event_t * const termina__ev, 
                              const uint32_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_u32(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_u64(const termina__event_t * const termina__ev, 
                            const uint64_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_u64(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_u64(const termina__event_t * const termina__ev, 
                              const uint64_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_u64(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_i8(const termina__event_t * const termina__ev, 
                           const int8_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_i8(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_i8(const termina__event_t * const termina__ev, 
                             const int8_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_i8(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_i16(const termina__event_t * const termina__ev, 
                            const int16_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_i16(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_i16(const termina__event_t * const termina__ev, 
                              const int16_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_i16(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_i32(const termina__event_t * const termina__ev, 
                            const int32_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_i32(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_i32(const termina__event_t * const termina__ev, 
                              const int32_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_i32(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_i64(const termina__event_t * const termina__ev, 
                            const int64_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);
        
    termina__os_sys_print__print_i64(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_i64(const termina__event_t * const termina__ev, 
                              const int64_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_i64(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__print_usize(const termina__event_t * const termina__ev, 
                              const size_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_usize(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type, 
                               termina__lock);

}

void SystemEntry__println_usize(const termina__event_t * const termina__ev,
                                const size_t value, const SysPrintBase base) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_usize(value, base);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type,
                               termina__lock);

}

void SystemEntry__print_f32(const termina__event_t * const termina__ev,
                            const float32_t value) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_f32(value);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type,
                               termina__lock);

}

void SystemEntry__println_f32(const termina__event_t * const termina__ev,
                              const float32_t value) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_f32(value);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type,
                               termina__lock);

}

void SystemEntry__print_f64(const termina__event_t * const termina__ev,
                            const float64_t value) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__print_f64(value);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type,
                               termina__lock);

}

void SystemEntry__println_f64(const termina__event_t * const termina__ev,
                              const float64_t value) {

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &system_entry._lock_type);

    termina__os_sys_print__println_f64(value);

    termina__resource__unlock(&termina__ev->owner, &system_entry._lock_type,
                               termina__lock);

}
