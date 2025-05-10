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
    ExceptSource__Task,
    ExceptSource__Handler
} __enum_ExceptSource_t;

/**
 * \brief Parameters for the Task variant of the ExceptSource type.
 */
typedef struct {
    size_t __0;
} __enum_ExceptSource__Task_params_t;

/**
 * \brief Parameters for the Handler variant of the ExceptSource type.
 */
typedef struct {
    size_t __0;
} __enum_ExceptSource__Handler_params_t;

/**
 * \brief Represents the ExceptSource type, which can be either Task or Handler.
 */
typedef struct {
    __enum_ExceptSource_t __variant;
    union {
        __enum_ExceptSource__Task_params_t Task;
        __enum_ExceptSource__Handler_params_t Handler;
    };
} ExceptSource;

/**
 * \brief Enumeration of possible exception types.
 */
typedef enum {
    Exception__EActionFailure,          /**< Action failure exception. */
    Exception__EMsgQueueSendError,      /**< Message queue send error exception. */
    Exception__EMsgQueueRecvError,      /**< Message queue receive error exception. */
    Exception__EArrayIndexOutOfBounds,  /**< Array index out of bounds exception. */
    Exception__EArraySliceOutOfBounds,  /**< Array slice out of bounds exception. */
    Exception__EArraySliceNegativeRange,/**< Array slice negative range exception. */
    Exception__EArraySliceInvalidRange  /**< Array slice invalid range exception. */
} __enum_Exception_t;

/**
 * \brief Parameters for the EActionFailure exception.
 */
typedef struct {
    ExceptSource __0; /**< Source of the exception. */
    size_t __1;       /**< ID of the source or sink port. */
    int32_t __2;      /**< Error code or status. */
} __enum_Exception__EActionFailure_params_t;

/**
 * \brief Parameters for the EMsgQueueSendError exception.
 */
typedef struct {
    size_t __0; /**< Message queue identifier. */
    int32_t __1; /**< Error code. */
} __enum_Exception__EMsgQueueSendError_params_t;

/**
 * \brief Parameters for the EMsgQueueRecvError exception.
 */
typedef struct {
    size_t __0; /**< Message queue identifier. */
    int32_t __1; /**< Error code. */
} __enum_Exception__EMsgQueueRecvError_params_t;

/**
 * \brief Parameters for the EArrayIndexOutOfBounds exception.
 */
typedef struct {
    size_t __0; /**< Address of the offending expression */
    size_t __1; /**< Size of the array. */
    size_t __2; /**< Offending index. */
} __enum_Exception__EArrayIndexOutOfBounds_params_t;

/**
 * \brief Parameters for the EArraySliceOutOfBounds exception.
 */
typedef struct {
    size_t __0; /**< Address of the offending expression. */
    size_t __1; /**< Size of the array. */
    size_t __2; /**< Upper bound of the slice. */
} __enum_Exception__EArraySliceOutOfBounds_params_t;

/**
 * \brief Parameters for the EArraySliceNegativeRange exception.
 */
typedef struct {
    size_t __0; /**< Address of the offending expression. */
    size_t __1; /**< Lower bound of the slice. */
    size_t __2; /**< Upper bound of the slice. */
} __enum_Exception__EArraySliceNegativeRange_params_t;

/**
 * \brief Parameters for the EArraySliceInvalidRange exception.
 */
typedef struct {
    size_t __0; /**< Address of the offending expression. */
    size_t __1; /**< Expected size of the array slice. */
    size_t __2; /**< Lower bound of the slice. */
    size_t __3; /**< Upper bound of the slice. */
} __enum_Exception__EArraySliceInvalidRange_params_t;

/**
 * \brief Represents the Exception type, which can be one of several exception variants.
 */
typedef struct {
    __enum_Exception_t __variant;
    union {
        __enum_Exception__EActionFailure_params_t EActionFailure; /**< Parameters for EActionFailure. */
        __enum_Exception__EMsgQueueSendError_params_t EMsgQueueSendError;   /**< Parameters for EMsgQueueSendError. */
        __enum_Exception__EMsgQueueRecvError_params_t EMsgQueueRecvError;   /**< Parameters for EMsgQueueRecvError. */
        __enum_Exception__EArrayIndexOutOfBounds_params_t EArrayIndexOutOfBounds; /**< Parameters for EArrayIndexOutOfBounds. */
        __enum_Exception__EArraySliceOutOfBounds_params_t EArraySliceOutOfBounds; /**< Parameters for EArraySliceOutOfBounds. */
        __enum_Exception__EArraySliceNegativeRange_params_t EArraySliceNegativeRange; /**< Parameters for EArraySliceNegativeRange. */
        __enum_Exception__EArraySliceInvalidRange_params_t EArraySliceInvalidRange; /**< Parameters for EArraySliceInvalidRange. */
    };
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

#endif // __TERMINA__PRELUDE_H__
