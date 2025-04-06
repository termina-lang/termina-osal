
#include <termina.h>

#include <termina/shared/system/sys_print.h>

void System__print__mutex_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print(str);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println__mutex_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println(str);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_char__mutex_lock(const char c) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_char(c);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_char__mutex_lock(const char c) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_char(c);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_u8__mutex_lock(const uint8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_u8(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_u8__mutex_lock(const uint8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_u8(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_u16__mutex_lock(const uint16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_u16(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_u16__mutex_lock(const uint16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_u16(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_u32__mutex_lock(const uint32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_u32(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_u32__mutex_lock(const uint32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_u32(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_u64__mutex_lock(const uint64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_u64(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_u64__mutex_lock(const uint64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_u64(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_i8__mutex_lock(const int8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_i8(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_i8__mutex_lock(const int8_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_i8(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_i16__mutex_lock(const int16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_i16(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_i16__mutex_lock(const int16_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_i16(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_i32__mutex_lock(const int32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_i32(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_i32__mutex_lock(const int32_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_i32(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_i64__mutex_lock(const int64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_i64(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_i64__mutex_lock(const int64_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_i64(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print_usize__mutex_lock(const size_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__print_usize(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__println_usize__mutex_lock(const size_t value, const SysPrintBase base) {

    Status status;
    status.__variant = Status__Success;

    __termina_mutex__lock(system.__mutex_id, &status);
    System__println_usize(value, base);
    __termina_mutex__unlock(system.__mutex_id, &status);
}

void System__print__task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print(str);
    __termina_task__unlock(lock);
}

void System__println__task_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println(str);
    __termina_task__unlock(lock);
}

void System__print_char__task_lock(const char c) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_char(c);
    __termina_task__unlock(lock);
}

void System__println_char__task_lock(const char c) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_char(c);
    __termina_task__unlock(lock);
}

void System__print_u8__task_lock(const uint8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_u8(value, base);
    __termina_task__unlock(lock);
}

void System__println_u8__task_lock(const uint8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_u8(value, base);
    __termina_task__unlock(lock);
}

void System__print_u16__task_lock(const uint16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_u16(value, base);
    __termina_task__unlock(lock);
}

void System__println_u16__task_lock(const uint16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_u16(value, base);
    __termina_task__unlock(lock);
}

void System__print_u32__task_lock(const uint32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_u32(value, base);
    __termina_task__unlock(lock);
}

void System__println_u32__task_lock(const uint32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_u32(value, base);
    __termina_task__unlock(lock);
}

void System__print_u64__task_lock(const uint64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_u64(value, base);
    __termina_task__unlock(lock);
}

void System__println_u64__task_lock(const uint64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_u64(value, base);
    __termina_task__unlock(lock);
}

void System__print_i8__task_lock(const int8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_i8(value, base);
    __termina_task__unlock(lock);
}

void System__println_i8__task_lock(const int8_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_i8(value, base);
    __termina_task__unlock(lock);
}

void System__print_i16__task_lock(const int16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_i16(value, base);
    __termina_task__unlock(lock);
}

void System__println_i16__task_lock(const int16_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_i16(value, base);
    __termina_task__unlock(lock);
}

void System__print_i32__task_lock(const int32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_i32(value, base);
    __termina_task__unlock(lock);
}

void System__println_i32__task_lock(const int32_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_i32(value, base);
    __termina_task__unlock(lock);
}

void System__print_i64__task_lock(const int64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_i64(value, base);
    __termina_task__unlock(lock);
}

void System__println_i64__task_lock(const int64_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_i64(value, base);
    __termina_task__unlock(lock);
}

void System__print_usize__task_lock(const size_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__print_usize(value, base);
    __termina_task__unlock(lock);
}

void System__println_usize__task_lock(const size_t value, const SysPrintBase base) {
    __termina_task_lock_t lock = __termina_task__lock();
    System__println_usize(value, base);
    __termina_task__unlock(lock);
}

void System__print__event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print(str);
    __termina_event__unlock(lock);
}

void System__println__event_lock(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println(str);
    __termina_event__unlock(lock);
}

void System__print_char__event_lock(const char c) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_char(c);
    __termina_event__unlock(lock);
}

void System__println_char__event_lock(const char c) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_char(c);
    __termina_event__unlock(lock);
}

void System__print_u8__event_lock(const uint8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_u8(value, base);
    __termina_event__unlock(lock);
}

void System__println_u8__event_lock(const uint8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_u8(value, base);
    __termina_event__unlock(lock);
}

void System__print_u16__event_lock(const uint16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_u16(value, base);
    __termina_event__unlock(lock);
}

void System__println_u16__event_lock(const uint16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_u16(value, base);
    __termina_event__unlock(lock);
}

void System__print_u32__event_lock(const uint32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_u32(value, base);
    __termina_event__unlock(lock);
}

void System__println_u32__event_lock(const uint32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_u32(value, base);
    __termina_event__unlock(lock);
}

void System__print_u64__event_lock(const uint64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_u64(value, base);
    __termina_event__unlock(lock);
}

void System__println_u64__event_lock(const uint64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_u64(value, base);
    __termina_event__unlock(lock);
}

void System__print_i8__event_lock(const int8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_i8(value, base);
    __termina_event__unlock(lock);
}

void System__println_i8__event_lock(const int8_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_i8(value, base);
    __termina_event__unlock(lock);
}

void System__print_i16__event_lock(const int16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_i16(value, base);
    __termina_event__unlock(lock);
}

void System__println_i16__event_lock(const int16_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_i16(value, base);
    __termina_event__unlock(lock);
}

void System__print_i32__event_lock(const int32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_i32(value, base);
    __termina_event__unlock(lock);
}

void System__println_i32__event_lock(const int32_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_i32(value, base);
    __termina_event__unlock(lock);
}

void System__print_i64__event_lock(const int64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_i64(value, base);
    __termina_event__unlock(lock);
}

void System__println_i64__event_lock(const int64_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_i64(value, base);
    __termina_event__unlock(lock);
}

void System__print_usize__event_lock(const size_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__print_usize(value, base);
    __termina_event__unlock(lock);
}

void System__println_usize__event_lock(const size_t value, const SysPrintBase base) {
    __termina_event_lock_t lock = __termina_event__lock();
    System__println_usize(value, base);
    __termina_event__unlock(lock);
}

