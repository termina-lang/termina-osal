#ifndef __TERMINA__EXCEPT_H__
#define __TERMINA__EXCEPT_H__

#include <termina/types.h>
#include <termina/prelude.h>


typedef void (*__termina_system_except_action_t) (void * const, const Exception);

typedef struct {

    void * handler_object;
    __termina_system_except_action_t handler_action;
    
} __termina_emitter_system_except_t;

extern __termina_emitter_system_except_t system_except;

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
void __termina_except__array_index_out_of_bounds(
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
void __termina_except__array_slice_out_of_bounds(
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
void __termina_except__array_slice_negative_range(
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
void __termina_except__array_slice_invalid_range(
    const size_t address,
    const size_t expected_size,
    const size_t lower_bound,
    const size_t upper_bound
);

/**
 * \brief Throws an action-failure exception.
 *
 * This function is called when the runtime detects an action-failure error.
 * 
 * @param[in] source        The source of the exception.
 * @param[in] sink_port_id  The ID of the source or sink port.
 * @param[in] error_code    The error code or status.
 * 
 */
void __termina_except__action_failure(
    const ExceptSource source,
    const size_t sink_port_id,
    const int32_t error_code
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
void __termina_except__msg_queue_send_error(
    const size_t msg_queue_id,
    const int32_t error_code
);


#endif // __TERMINA__EXCEPT_H__
