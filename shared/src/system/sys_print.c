
#include <termina.h>

#include <termina/shared/system/sys_print.h>

__termina_sys_print_t __termina_sys_print;

void __termina_sys_print__print_mutex(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print(str);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_mutex(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println(str);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_char_mutex(const char c) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_char(c);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_char_mutex(const char c) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_char(c);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_u8_mutex(const uint8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_u8(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_u8_mutex(const uint8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_u8(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_u16_mutex(const uint16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_u16(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_u16_mutex(const uint16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_u16(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_u32_mutex(const uint32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_u32(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_u32_mutex(const uint32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_u32(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_u64_mutex(const uint64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_u64(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_u64_mutex(const uint64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_u64(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_i8_mutex(const int8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_i8(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_i8_mutex(const int8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_i8(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_i16_mutex(const int16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_i16(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_i16_mutex(const int16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_i16(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_i32_mutex(const int32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_i32(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_i32_mutex(const int32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_i32(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_i64_mutex(const int64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_i64(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_i64_mutex(const int64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_i64(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_usize_mutex(const size_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__print_usize(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__println_usize_mutex(const size_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(__termina_sys_print.mutex_id, &status);
    __termina_sys_print__println_usize(value, base);
    __termina_mutex__unlock(__termina_sys_print.mutex_id, &status);
}

void __termina_sys_print__print_task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print(str);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println(str);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_char_task_lock(const char c) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_char(c);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_char_task_lock(const char c) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_char(c);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_u8_task_lock(const uint8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_u8(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_u8_task_lock(const uint8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_u8(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_u16_task_lock(const uint16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_u16(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_u16_task_lock(const uint16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_u16(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_u32_task_lock(const uint32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_u32(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_u32_task_lock(const uint32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_u32(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_u64_task_lock(const uint64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_u64(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_u64_task_lock(const uint64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_u64(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_i8_task_lock(const int8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_i8(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_i8_task_lock(const int8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_i8(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_i16_task_lock(const int16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_i16(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_i16_task_lock(const int16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_i16(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_i32_task_lock(const int32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_i32(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_i32_task_lock(const int32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_i32(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_i64_task_lock(const int64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_i64(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_i64_task_lock(const int64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_i64(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_usize_task_lock(const size_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__print_usize(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__println_usize_task_lock(const size_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    __termina_sys_print__println_usize(value, base);
    __termina_task__unlock(lock);
}

void __termina_sys_print__print_event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print(str);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println(str);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_char_event_lock(const char c) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_char(c);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_char_event_lock(const char c) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_char(c);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_u8_event_lock(const uint8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_u8(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_u8_event_lock(const uint8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_u8(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_u16_event_lock(const uint16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_u16(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_u16_event_lock(const uint16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_u16(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_u32_event_lock(const uint32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_u32(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_u32_event_lock(const uint32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_u32(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_u64_event_lock(const uint64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_u64(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_u64_event_lock(const uint64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_u64(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_i8_event_lock(const int8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_i8(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_i8_event_lock(const int8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_i8(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_i16_event_lock(const int16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_i16(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_i16_event_lock(const int16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_i16(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_i32_event_lock(const int32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_i32(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_i32_event_lock(const int32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_i32(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_i64_event_lock(const int64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_i64(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_i64_event_lock(const int64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_i64(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__print_usize_event_lock(const size_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__print_usize(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__println_usize_event_lock(const size_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    __termina_sys_print__println_usize(value, base);
    __termina_event__unlock(lock);
}

void __termina_sys_print__init() {

    __termina_sys_print.print = __termina_sys_print__print;
    __termina_sys_print.println = __termina_sys_print__println;

    __termina_sys_print.print_char = __termina_sys_print__print_char;
    __termina_sys_print.println_char = __termina_sys_print__println_char;

    __termina_sys_print.print_u8 = __termina_sys_print__print_u8;
    __termina_sys_print.println_u8 = __termina_sys_print__println_u8;

    __termina_sys_print.print_u16 = __termina_sys_print__print_u16;
    __termina_sys_print.println_u16 = __termina_sys_print__println_u16;
    
    __termina_sys_print.print_u32 = __termina_sys_print__print_u32;
    __termina_sys_print.println_u32 = __termina_sys_print__println_u32;

    __termina_sys_print.print_u64 = __termina_sys_print__print_u64;
    __termina_sys_print.println_u64 = __termina_sys_print__println_u64;

    __termina_sys_print.print_i8 = __termina_sys_print__print_i8;
    __termina_sys_print.println_i8 = __termina_sys_print__println_i8;

    __termina_sys_print.print_i16 = __termina_sys_print__print_i16;
    __termina_sys_print.println_i16 = __termina_sys_print__println_i16;

    __termina_sys_print.print_i32 = __termina_sys_print__print_i32;
    __termina_sys_print.println_i32 = __termina_sys_print__println_i32;

    __termina_sys_print.print_i64 = __termina_sys_print__print_i64;
    __termina_sys_print.println_i64 = __termina_sys_print__println_i64;

    __termina_sys_print.print_usize = __termina_sys_print__print_usize;
    __termina_sys_print.println_usize = __termina_sys_print__println_usize;

    return;

}
