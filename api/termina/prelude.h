#ifndef TERMINA__PRELUDE_H__
#define TERMINA__PRELUDE_H__

#include <termina/types.h>

/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    Result__Ok,
    Result__Error 
} termina__enum__Result_t;

/**
 * \brief Enumeration of the possible variants of the Status type.
 */
typedef enum {
    Status__Success,
    Status__Failure
} termina__enum__Status_t;

typedef struct {
    int32_t _0;
} termina__enum__Status__i32__Failure_params_t;

typedef struct {
    termina__enum__Status__i32__Failure_params_t Failure;
    termina__enum__Status_t _variant;
} Status__i32;

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
} termina__enum__ExceptSource_t;

/**
 * \brief Parameters for the Task variant of the ExceptSource type.
 */
typedef struct {
    size_t _0;
} termina__enum__ExceptSource__Task_params_t;

/**
 * \brief Parameters for the Handler variant of the ExceptSource type.
 */
typedef struct {
    size_t _0;
} termina__enum__ExceptSource__Handler_params_t;

/**
 * \brief Represents the ExceptSource type, which can be either Task or Handler.
 */
typedef struct {
    termina__enum__ExceptSource_t _variant;
    union {
        termina__enum__ExceptSource__Task_params_t Task;
        termina__enum__ExceptSource__Handler_params_t Handler;
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
    Exception__EArraySliceInvalidRange, /**< Array slice invalid range exception. */
    Exception__EShiftAmountOutOfBounds  /**< Shift amount out of bounds exception. */
} termina__enum__Exception_t;

/**
 * \brief Parameters for the EActionFailure exception.
 */
typedef struct {
    ExceptSource _0; /**< Source of the exception. */
    size_t _1;       /**< ID of the source or sink port. */
    int32_t _2;      /**< Result__Error code or status. */
} termina__enum__Exception__EActionFailure_params_t;

/**
 * \brief Parameters for the EMsgQueueSendError exception.
 */
typedef struct {
    size_t _0; /**< Message queue identifier. */
    int32_t _1; /**< Result__Error code. */
} termina__enum__Exception__EMsgQueueSendError_params_t;

/**
 * \brief Parameters for the EMsgQueueRecvError exception.
 */
typedef struct {
    size_t _0; /**< Message queue identifier. */
    int32_t _1; /**< Result__Error code. */
} termina__enum__Exception__EMsgQueueRecvError_params_t;

/**
 * \brief Parameters for the EArrayIndexOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression */
    size_t _1; /**< Size of the array. */
    size_t _2; /**< Offending index. */
} termina__enum__Exception__EArrayIndexOutOfBounds_params_t;

/**
 * \brief Parameters for the EArraySliceOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Size of the array. */
    size_t _2; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceOutOfBounds_params_t;

/**
 * \brief Parameters for the EArraySliceNegativeRange exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Lower bound of the slice. */
    size_t _2; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceNegativeRange_params_t;

/**
 * \brief Parameters for the EArraySliceInvalidRange exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Expected size of the array slice. */
    size_t _2; /**< Lower bound of the slice. */
    size_t _3; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceInvalidRange_params_t;

/**
 * \brief Parameters for the EShiftAmountOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Bit width of the shifted type. */
    size_t _2; /**< Offending shift amount. */
} termina__enum__Exception__EShiftAmountOutOfBounds_params_t;

/**
 * \brief Represents the Exception type, which can be one of several exception variants.
 */
typedef struct {
    termina__enum__Exception_t _variant;
    union {
        termina__enum__Exception__EActionFailure_params_t EActionFailure; /**< Parameters for EActionFailure. */
        termina__enum__Exception__EMsgQueueSendError_params_t EMsgQueueSendError;   /**< Parameters for EMsgQueueSendError. */
        termina__enum__Exception__EMsgQueueRecvError_params_t EMsgQueueRecvError;   /**< Parameters for EMsgQueueRecvError. */
        termina__enum__Exception__EArrayIndexOutOfBounds_params_t EArrayIndexOutOfBounds; /**< Parameters for EArrayIndexOutOfBounds. */
        termina__enum__Exception__EArraySliceOutOfBounds_params_t EArraySliceOutOfBounds; /**< Parameters for EArraySliceOutOfBounds. */
        termina__enum__Exception__EArraySliceNegativeRange_params_t EArraySliceNegativeRange; /**< Parameters for EArraySliceNegativeRange. */
        termina__enum__Exception__EArraySliceInvalidRange_params_t EArraySliceInvalidRange; /**< Parameters for EArraySliceInvalidRange. */
        termina__enum__Exception__EShiftAmountOutOfBounds_params_t EShiftAmountOutOfBounds; /**< Parameters for EShiftAmountOutOfBounds. */
    };
} Exception;

typedef struct {
    TimeVal period;
} PeriodicTimer;

typedef enum {
    SysPrintBase__Decimal,
    SysPrintBase__Hexadecimal
} termina__enum__SysPrintBase_t;

typedef struct {
    termina__enum__SysPrintBase_t _variant;
} SysPrintBase;

#endif // TERMINA__PRELUDE_H__
