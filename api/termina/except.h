#ifndef TERMINA__EXCEPT_H__
#define TERMINA__EXCEPT_H__

#include <termina/types.h>
#include <termina/prelude.h>


/**
 * \brief Action that attends an exception of the system.
 *
 * It receives the event, as the actions connected to the other emitters do,
 * and returns nothing, because the system reboots as soon as it finishes.
 */
typedef void (*termina__system_except_action_t)(const termina__event_t * const, void * const, const Exception);

/**
 * \brief Connection of the system exception emitter to the handler that
 *        attends it.
 *
 * Only a handler can attend the emitter, so the connection has no task arm.
 */
typedef struct {

    //! Pointer to the handler object
    void * handler_object;

    //! Identifier of the handler
    termina__id_t handler_id;

    //! Pointer to the handler function
    termina__system_except_action_t handler_action;

} termina__system_except_connection_t;

/**
 * \brief Registers the handler that attends the exceptions of the system.
 *
 * The runtime copies the connection. Until this function is called, an
 * exception reboots the system without calling any handler.
 *
 * @param[in] emitter_id  the identifier of the system exception emitter.
 * @param[in] connection  the handler that attends the exceptions.
 */
void termina__except__init_emitter(const termina__id_t emitter_id,
                                   const termina__system_except_connection_t * const connection);

/**
 * \brief Throws an array-index-out-of-bounds exception.
 *
 * This function is called when the runtime detects an array-index-out-of-bounds
 * error.
 * 
 * @param[in] address The address of the offending expression.
 * @param[in] array_size The size of the array.
 * @param[in] index The offending index.
 * 
 */
_Noreturn void termina__except__array_index_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t index
);

/**
 * \brief Throws an array-slice-out-of-bounds exception.
 *
 * This function is called when the runtime detects an array-slice-out-of-bounds
 * error.
 * 
 * @param[in] address The address of the offending expression.
 * @param[in] array_size The size of the array.
 * @param[in] upper_bound The upper bound of the slice.
 * 
 */
_Noreturn void termina__except__array_slice_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t upper_bound
);

/**
 * \brief Throws an array-slice-negative-range exception.
 *
 * This function is called when the runtime detects an array-slice-negative-range
 * error.
 * 
 * @param[in] address The address of the offending expression.
 * @param[in] lower_bound The lower bound of the slice.
 * @param[in] upper_bound The upper bound of the slice.
 * 
 */
_Noreturn void termina__except__array_slice_negative_range(
    const size_t address,
    const size_t lower_bound,
    const size_t upper_bound
);

/**
 * \brief Throws an array-slice-invalid-range exception.
 *
 * This function is called when the runtime detects an array-slice-invalid-range
 * error.
 * 
 * @param[in] address The address of the offending expression.
 * @param[in] expected_size The expected size of the array slice.
 * @param[in] lower_bound The lower bound of the slice.
 * @param[in] upper_bound The upper bound of the slice.
 * 
 */
_Noreturn void termina__except__array_slice_invalid_range(
    const size_t address,
    const size_t expected_size,
    const size_t lower_bound,
    const size_t upper_bound
);

/**
 * \brief Throws a shift-amount-out-of-bounds exception.
 *
 * This function is called when the runtime detects a shift whose amount is
 * greater than or equal to the bit width of the shifted type.
 *
 * @param[in] address The address of the offending expression.
 * @param[in] width   The bit width of the shifted type.
 * @param[in] amount  The offending shift amount.
 *
 */
_Noreturn void termina__except__shift_amount_out_of_bounds(
    const size_t address,
    const size_t width,
    const size_t amount
);

/**
 * \brief Throws an arithmetic-overflow exception.
 *
 * This function is called when the runtime detects a signed arithmetic
 * operation whose result falls outside the range of its type.
 *
 * @param[in] address The address of the offending expression.
 *
 */
_Noreturn void termina__except__arithmetic_overflow(
    const size_t address
);

/**
 * \brief Throws a division-by-zero exception.
 *
 * This function is called when the runtime detects a division or a remainder
 * whose divisor is zero.
 *
 * @param[in] address The address of the offending expression.
 *
 */
_Noreturn void termina__except__division_by_zero(
    const size_t address
);

/**
 * \brief Throws a message-queue-send-error exception.
 *
 * This function is called when the runtime detects an error while sending a
 * message to a message queue.
 * 
 * @param[in] msg_queue_id The message queue identifier.
 * @param[in] error_code   The error code.
 * 
 */
_Noreturn void termina__except__msg_queue_send_error(
    const size_t msg_queue_id,
    const termina__error_code_t error_code
);

/**
 * \brief Throws a message-queue-recv-error exception.
 *
 * This function is called when the runtime detects an error while receiving a
 * message from a message queue.
 * 
 * @param[in] msg_queue_id The message queue identifier.
 * @param[in] error_code   The error code.
 * 
 */
_Noreturn void termina__except__msg_queue_recv_error(
    const size_t msg_queue_id,
    const termina__error_code_t error_code
);

/**
 * \brief Operations of the runtime whose failure raises ERuntimeFailure. The
 *        exception carries the value as a number, and the values are part of
 *        the interface that a system_except handler decodes.
 */
typedef enum {
    termina__runtime_operation__mutex_lock = 0,   /**< Taking a mutex. */
    termina__runtime_operation__mutex_unlock = 1, /**< Giving a mutex back. */
    termina__runtime_operation__timer_arm = 2,    /**< Arming a periodic timer. */
    termina__runtime_operation__task_ready = 3,   /**< Making a task ready to run. */
    termina__runtime_operation__pool_free = 4,    /**< Returning a block to its pool. */
    termina__runtime_operation__task_dispatch = 5, /**< Dispatching an event to the action of a task. */
    termina__runtime_operation__irq_dispatch = 6, /**< Dispatching an interrupt to its handler. */
    termina__runtime_operation__deque_put = 7,    /**< Putting a box into a deque. */
    termina__runtime_operation__pool_alloc = 8,   /**< Taking a block from its pool. */
    termina__runtime_operation__task_priority = 9, /**< Changing the priority of a task. */
    termina__runtime_operation__test_reset = 10   /**< Resetting the deployment before a case of a test. */
} termina__runtime_operation_t;

/**
 * \brief Throws a runtime-failure exception.
 *
 * This function is called when an operation of the runtime, or of the
 * operating system under it, fails in a way that the application cannot
 * handle.
 *
 * @param[in] operation   The operation that failed.
 * @param[in] error_code  The error code of the operation.
 *
 */
_Noreturn void termina__except__runtime_failure(
    const termina__runtime_operation_t operation,
    const termina__error_code_t error_code
);

/**
 * \brief Throws a processor-fault exception.
 *
 * This function is called by the back-end when the processor raises an
 * exception, such as an invalid memory access or an illegal instruction.
 *
 * @param[in] kind     Exception number of the architecture.
 * @param[in] status   Fault status register, or 0 when there is none.
 * @param[in] pc       Address of the instruction that failed, or 0.
 * @param[in] address  Faulting address, or 0 when the architecture gives none.
 *
 */
_Noreturn void termina__except__processor_fault(
    const uint32_t kind,
    const uint32_t status,
    const size_t pc,
    const size_t address
);

/**
 * \brief Throws a kernel-failure exception.
 *
 * This function is called by the back-end when the operating system raises a
 * fatal error of its own.
 *
 * @param[in] source  Source of the fatal error, as the operating system
 *                    numbers it.
 * @param[in] code    Code of the fatal error, which may be an address.
 *
 */
_Noreturn void termina__except__kernel_failure(
    const uint32_t source,
    const size_t code
);

/**
 * \brief Throws a stack-overflow exception.
 *
 * This function is called by the back-end when the operating system finds
 * that a stack has overflowed.
 *
 * @param[in] task_id  Identifier of the task, or TERMINA__ID__INVALID when the
 *                     stack is not of a task of the application.
 *
 */
_Noreturn void termina__except__stack_overflow(
    const termina__id_t task_id
);


#endif // TERMINA__EXCEPT_H__
