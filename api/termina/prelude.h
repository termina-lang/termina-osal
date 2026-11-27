/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief C types of the Termina prelude: `Result`, `Status`, `TimeVal`,
 *        `Exception`, `PeriodicTimer` and `SysPrintBase`.
 */

#ifndef TERMINA__PRELUDE_H__
#define TERMINA__PRELUDE_H__

#include <termina/types.h>

/**
 * @brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    Result__Ok,
    Result__Error 
} termina__enum__Result_t;

/**
 * @brief Enumeration of the possible variants of the Status type.
 */
typedef enum {
    Status__Success,
    Status__Failure
} termina__enum__Status_t;

/**
 * @brief Structure that implements the TimeVal type.
 */
typedef struct {
    //! Seconds.
    uint32_t tv_sec;
    //! Microseconds.
    uint32_t tv_usec;
} TimeVal;

/**
 * @brief Enumeration of the possible variants of the Exception type.
 */
typedef enum {
    Exception__EMsgQueueSendError,      /**< Message queue send error exception. */
    Exception__EMsgQueueRecvError,      /**< Message queue receive error exception. */
    Exception__EArrayIndexOutOfBounds,  /**< Array index out of bounds exception. */
    Exception__EArraySliceOutOfBounds,  /**< Array slice out of bounds exception. */
    Exception__EArraySliceNegativeRange,/**< Array slice negative range exception. */
    Exception__EArraySliceInvalidRange, /**< Array slice invalid range exception. */
    Exception__EShiftAmountOutOfBounds, /**< Shift amount out of bounds exception. */
    Exception__EArithmeticOverflow,     /**< Signed arithmetic overflow exception. */
    Exception__EDivisionByZero,         /**< Division or remainder by zero exception. */
    Exception__ERuntimeFailure,         /**< Failure of the runtime itself. */
    Exception__EProcessorFault,         /**< Fault of the processor. */
    Exception__EKernelFailure,          /**< Fatal error raised by the operating system itself. */
    Exception__EStackOverflow           /**< Stack overflow detected by the operating system. */
} termina__enum__Exception_t;

/**
 * @brief Parameters for the EMsgQueueSendError exception.
 */
typedef struct {
    size_t _0; /**< Address of the call to the runtime that sent the message, or 0. */
    size_t _1; /**< Message queue identifier. */
    int32_t _2; /**< Error code. */
} termina__enum__Exception__EMsgQueueSendError_params_t;

/**
 * @brief Parameters for the EMsgQueueRecvError exception.
 */
typedef struct {
    size_t _0; /**< Message queue identifier. */
    int32_t _1; /**< Error code. */
} termina__enum__Exception__EMsgQueueRecvError_params_t;

/**
 * @brief Parameters for the EArrayIndexOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Size of the array. */
    size_t _2; /**< Offending index. */
} termina__enum__Exception__EArrayIndexOutOfBounds_params_t;

/**
 * @brief Parameters for the EArraySliceOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Size of the array. */
    size_t _2; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceOutOfBounds_params_t;

/**
 * @brief Parameters for the EArraySliceNegativeRange exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Lower bound of the slice. */
    size_t _2; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceNegativeRange_params_t;

/**
 * @brief Parameters for the EArraySliceInvalidRange exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Expected size of the array slice. */
    size_t _2; /**< Lower bound of the slice. */
    size_t _3; /**< Upper bound of the slice. */
} termina__enum__Exception__EArraySliceInvalidRange_params_t;

/**
 * @brief Parameters for the EShiftAmountOutOfBounds exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
    size_t _1; /**< Bit width of the shifted type. */
    size_t _2; /**< Offending shift amount. */
} termina__enum__Exception__EShiftAmountOutOfBounds_params_t;

/**
 * @brief Parameters for the EArithmeticOverflow exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
} termina__enum__Exception__EArithmeticOverflow_params_t;

/**
 * @brief Parameters for the EDivisionByZero exception.
 */
typedef struct {
    size_t _0; /**< Address of the offending expression. */
} termina__enum__Exception__EDivisionByZero_params_t;

/**
 * @brief Parameters for the ERuntimeFailure exception.
 */
typedef struct {
    size_t _0;   /**< Address of the call to the runtime that failed, or 0. */
    uint32_t _1; /**< Operation of the runtime that failed. */
    int32_t _2;  /**< Error code of the operation, as a value of termina__error_code_t. */
} termina__enum__Exception__ERuntimeFailure_params_t;

/**
 * @brief Parameters for the EProcessorFault exception.
 *
 * The values are those of the platform and are decoded according to it.
 */
typedef struct {
    uint32_t _0; /**< Exception number of the architecture. */
    uint32_t _1; /**< Fault status register, or 0 when there is none. */
    size_t _2;   /**< Address of the instruction that failed, or 0. */
    size_t _3;   /**< Faulting address, or 0 when the architecture gives none. */
} termina__enum__Exception__EProcessorFault_params_t;

/**
 * @brief Parameters for the EKernelFailure exception.
 */
typedef struct {
    uint32_t _0; /**< Source of the fatal error, as the operating system numbers it. */
    size_t _1;   /**< Code of the fatal error, which may be an address. */
} termina__enum__Exception__EKernelFailure_params_t;

/**
 * @brief Parameters for the EStackOverflow exception.
 */
typedef struct {
    size_t _0; /**< Identifier of the task, or TERMINA__ID__INVALID when the stack is not of a task of the application. */
} termina__enum__Exception__EStackOverflow_params_t;

/**
 * @brief Structure that implements the Exception type.
 */
typedef struct {
    //! Variant of the exception.
    termina__enum__Exception_t _variant;
    union {
        termina__enum__Exception__EMsgQueueSendError_params_t EMsgQueueSendError;   /**< Parameters for EMsgQueueSendError. */
        termina__enum__Exception__EMsgQueueRecvError_params_t EMsgQueueRecvError;   /**< Parameters for EMsgQueueRecvError. */
        termina__enum__Exception__EArrayIndexOutOfBounds_params_t EArrayIndexOutOfBounds; /**< Parameters for EArrayIndexOutOfBounds. */
        termina__enum__Exception__EArraySliceOutOfBounds_params_t EArraySliceOutOfBounds; /**< Parameters for EArraySliceOutOfBounds. */
        termina__enum__Exception__EArraySliceNegativeRange_params_t EArraySliceNegativeRange; /**< Parameters for EArraySliceNegativeRange. */
        termina__enum__Exception__EArraySliceInvalidRange_params_t EArraySliceInvalidRange; /**< Parameters for EArraySliceInvalidRange. */
        termina__enum__Exception__EShiftAmountOutOfBounds_params_t EShiftAmountOutOfBounds; /**< Parameters for EShiftAmountOutOfBounds. */
        termina__enum__Exception__EArithmeticOverflow_params_t EArithmeticOverflow; /**< Parameters for EArithmeticOverflow. */
        termina__enum__Exception__EDivisionByZero_params_t EDivisionByZero; /**< Parameters for EDivisionByZero. */
        termina__enum__Exception__ERuntimeFailure_params_t ERuntimeFailure; /**< Parameters for ERuntimeFailure. */
        termina__enum__Exception__EProcessorFault_params_t EProcessorFault; /**< Parameters for EProcessorFault. */
        termina__enum__Exception__EKernelFailure_params_t EKernelFailure; /**< Parameters for EKernelFailure. */
        termina__enum__Exception__EStackOverflow_params_t EStackOverflow; /**< Parameters for EStackOverflow. */
    };
} Exception;

/**
 * @brief Structure that implements the PeriodicTimer type.
 */
typedef struct {
    //! Period of the timer.
    TimeVal period;
} PeriodicTimer;

/**
 * @brief Enumeration of the possible variants of the SysPrintBase type.
 */
typedef enum {
    SysPrintBase__Decimal,
    SysPrintBase__Hexadecimal
} termina__enum__SysPrintBase_t;

/**
 * @brief Structure that implements the SysPrintBase type, the base in which
 *        an integer is printed.
 */
typedef struct {
    termina__enum__SysPrintBase_t _variant;
} SysPrintBase;

#endif // TERMINA__PRELUDE_H__
