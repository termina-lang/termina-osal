#ifndef __TERMINA__SYSTEM__SYS_PRINT_H__
#define __TERMINA__SYSTEM__SYS_PRINT_H__

#include <termina/types.h>

typedef enum {
    SysPrintBase__Decimal,
    SysPrintBase__Hexadecimal
} __enum_SysPrintBase_t;

typedef struct {
    __enum_SysPrintBase_t __variant;
} SysPrintBase;

typedef struct {

    // \brief Mutex used to protect the system print functions
    __termina_id_t mutex_id;

    // \brief Print a string
    void (*print)(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);
    // \brief Print a string followed by a newline
    void (*println)(const char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE]);

    // \brief Print a character
    void (*print_char)(const char value);
    // \brief Print a character followed by a newline
    void (*println_char)(const char value);

    // \brief Print an unsigned 8-bit integer
    void (*print_u8)(const uint8_t value, const SysPrintBase base);
    // \brief Print an unsigned 8-bit integer followed by a newline    
    void (*println_u8)(const uint8_t value, const SysPrintBase base);

    // \brief Print an unsigned 16-bit integer
    void (*print_u16)(const uint16_t value, const SysPrintBase base);
    // \brief Print an unsigned 16-bit integer followed by a newline
    void (*println_u16)(const uint16_t value, const SysPrintBase base);
    
    // \brief Print an unsigned 32-bit integer
    void (*print_u32)(const uint32_t value, const SysPrintBase base);
    // \brief Print an unsigned 32-bit integer followed by a newline
    void (*println_u32)(const uint32_t value, const SysPrintBase base);

    // \brief Print an unsigned 64-bit integer
    void (*print_u64)(const uint64_t value, const SysPrintBase base);
    // \brief Print an unsigned 64-bit integer followed by a newline
    void (*println_u64)(const uint64_t value, const SysPrintBase base);

    // \brief Print a signed 8-bit integer
    void (*print_i8)(const int8_t value, const SysPrintBase base);
    // \brief Print a signed 8-bit integer followed by a newline
    void (*println_i8)(const int8_t value, const SysPrintBase base);

    // \brief Print a signed 16-bit integer
    void (*print_i16)(const int16_t value, const SysPrintBase base);
    // \brief Print a signed 16-bit integer followed by a newline
    void (*println_i16)(const int16_t value, const SysPrintBase base);

    // \brief Print a signed 32-bit integer
    void (*print_i32)(const int32_t value, const SysPrintBase base);
    // \brief Print a signed 32-bit integer followed by a newline
    void (*println_i32)(const int32_t value, const SysPrintBase base);

    // \brief Print a signed 64-bit integer
    void (*print_i64)(const int64_t value, const SysPrintBase base);
    // \brief Print a signed 64-bit integer followed by a newline
    void (*println_i64)(const int64_t value, const SysPrintBase base);

    // \brief Print a usize integer
    void (*print_usize)(const size_t value, const SysPrintBase base);
    // \brief Print a usize integer followed by a newline
    void (*println_usize)(const size_t value, const SysPrintBase base);

} __termina_sys_print_t;

extern __termina_sys_print_t __termina_sys_print;

void __termina_sys_print__init(void);
void __termina_sys_print__init_mutex(__termina_id_t mutex_id);
void __termina_sys_print__init_task_lock(void);
void __termina_sys_print__init_event_lock(void);

#endif // __TERMINA__SYSTEM__SYS_PRINT_H__