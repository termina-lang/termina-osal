#ifndef __TERMINA__PRELUDE_H__
#define __TERMINA__PRELUDE_H__

#include <termina/types.h>

/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    Ok,
    Error 
} __enum_result_t;

/**
 * \brief Enumeration of the possible variants of the Status type.
 */
typedef enum {
    Success,
    Failure
} __enum_status_t;

typedef struct {
    int32_t __0;
} __status_int32__Failure_params_t;

typedef struct {
    __status_int32__Failure_params_t Failure;
    __enum_status_t __variant;
} __status_int32_t;

/**
 * \brief Structure that implements the TimeVal type.
 */
typedef struct {
    uint32_t tv_sec;
    uint32_t tv_usec;
} TimeVal;

typedef enum {
    Exception__InternalError,
    Exception__QueueFull
} __enum_Exception_t;

typedef struct {
    //! Identifier of the message queue that is full.
    size_t __0;
} __enum_Exception__QueueFull_params_t;

typedef struct {
    __enum_Exception_t __variant;
    __enum_Exception__QueueFull_params_t QueueFull;
} Exception;

typedef struct {
    TimeVal period;
} PeriodicTimer;

typedef enum {
    SysPrintBase__Decimal,
    SysPrintBase__Hexadecimal
} __enum_SysPrintBase_t;

typedef struct {
    __enum_SysPrintBase_t __variant;
} SysPrintBase;

typedef struct {
    __termina_id_t __mutex_id;
} SystemEntry;

#endif // __TERMINA__PRELUDE_H__
