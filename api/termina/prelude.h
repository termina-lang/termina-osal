#ifndef __TERMINA__PRELUDE_H__
#define __TERMINA__PRELUDE_H__

#include <termina/types.h>

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

typedef enum {
    Status__Success,
    Status__Error
} __enum_Status_t;

typedef struct {
    Exception __0;
} __enum_Status__Error_params_t;

typedef struct {
    __enum_Status_t __variant;
    __enum_Status__Error_params_t Error;
} Status;

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
