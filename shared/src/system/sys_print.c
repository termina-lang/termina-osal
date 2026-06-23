
#include <termina.h>
#include <termina/shared/system/sys_print.h>

void SystemEntry__print(const __termina_event_t * const __ev,
                        const char str[__TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE]) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print(str);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println(const __termina_event_t * const __ev, 
                          const char str[__TERMINA_SYS_PRINT_OUTPUT_BUFFER_SIZE]) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println(str);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_char(const __termina_event_t * const __ev, 
                             const char c) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_char(c);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);
}

void SystemEntry__println_char(const __termina_event_t * const __ev, 
                               const char c) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_char(c);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_u8(const __termina_event_t * const __ev, 
                           const uint8_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_u8(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_u8(const __termina_event_t * const __ev, 
                             const uint8_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_u8(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_u16(const __termina_event_t * const __ev, 
                            const uint16_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_u16(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_u16(const __termina_event_t * const __ev, 
                              const uint16_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_u16(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_u32(const __termina_event_t * const __ev, 
                            const uint32_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_u32(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_u32(const __termina_event_t * const __ev, 
                              const uint32_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_u32(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_u64(const __termina_event_t * const __ev, 
                            const uint64_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_u64(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_u64(const __termina_event_t * const __ev, 
                              const uint64_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_u64(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_i8(const __termina_event_t * const __ev, 
                           const int8_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_i8(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_i8(const __termina_event_t * const __ev, 
                             const int8_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_i8(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_i16(const __termina_event_t * const __ev, 
                            const int16_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_i16(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_i16(const __termina_event_t * const __ev, 
                              const int16_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_i16(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_i32(const __termina_event_t * const __ev, 
                            const int32_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_i32(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_i32(const __termina_event_t * const __ev, 
                              const int32_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_i32(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_i64(const __termina_event_t * const __ev, 
                            const int64_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);
        
    __termina_os_sys_print__print_i64(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_i64(const __termina_event_t * const __ev, 
                              const int64_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_i64(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__print_usize(const __termina_event_t * const __ev, 
                              const size_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_usize(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type, 
                               __lock);

}

void SystemEntry__println_usize(const __termina_event_t * const __ev,
                                const size_t value, const SysPrintBase base) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_usize(value, base);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type,
                               __lock);

}

void SystemEntry__print_f32(const __termina_event_t * const __ev,
                            const float32_t value) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_f32(value);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type,
                               __lock);

}

void SystemEntry__println_f32(const __termina_event_t * const __ev,
                              const float32_t value) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_f32(value);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type,
                               __lock);

}

void SystemEntry__print_f64(const __termina_event_t * const __ev,
                            const float64_t value) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__print_f64(value);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type,
                               __lock);

}

void SystemEntry__println_f64(const __termina_event_t * const __ev,
                              const float64_t value) {

    __termina_lock_t __lock = __termina_resource__lock(
        &__ev->owner, &system_entry.__lock_type);

    __termina_os_sys_print__println_f64(value);

    __termina_resource__unlock(&__ev->owner, &system_entry.__lock_type,
                               __lock);

}
