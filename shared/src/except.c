
#include <termina.h>
#include <termina/shared/except.h>
#include <termina/shared/exec.h>

termina__emitter_system_except_t system_except;

void termina__except__init_emitter(const termina__id_t emitter_id,
                                   const termina__system_except_connection_t * const connection) {

    system_except.emitter_id = emitter_id;
    system_except.connection = *connection;

    termina__os__except__init_emitter();

}

/**
 * \brief Raises an exception, which is the one path every exception takes.
 *
 * The handler of the application runs when one is registered, and the system
 * reboots afterwards either way: the exceptions this runtime raises are the
 * ones it cannot recover from, so the handler records the cause and the system
 * restarts. Every back-end behaves the same, and what is left of the operating
 * system is the quiesce, which stops whatever could run in the middle.
 */
static _Noreturn void termina__shared__except__raise(const Exception except) {

    // Set before the handler runs and never cleared: an exception raised while
    // the handler is running is a failure of the handler itself, and the system
    // reboots without calling it a second time. The read and the write need no
    // atomic, because the quiesce below has already disabled the interrupts of
    // the processor and nothing else runs between them.
    static _Bool servicing = false;

    termina__os__exec__quiesce();

    if ((NULL != system_except.connection.handler_action) && (!servicing)) {

        termina__event_t event = {
            .emitter_id = system_except.emitter_id,
            .owner.type = termina__active_entity__handler,
            .owner.handler.handler_id = system_except.connection.handler_id,
            // The handler has a single sink port, so the port is always 0
            .port_id = 0
        };

        servicing = true;

        system_except.connection.handler_action(&event,
                                                system_except.connection.handler_object,
                                                except);

    }

    termina__exec__reboot();

}

void termina__except__shift_amount_out_of_bounds(
    const size_t address,
    const size_t width,
    const size_t amount) {

    Exception except;
    except._variant = Exception__EShiftAmountOutOfBounds;
    except.EShiftAmountOutOfBounds._0 = address;
    except.EShiftAmountOutOfBounds._1 = width;
    except.EShiftAmountOutOfBounds._2 = amount;

    termina__shared__except__raise(except);

}

void termina__except__arithmetic_overflow(
    const size_t address) {

    Exception except;
    except._variant = Exception__EArithmeticOverflow;
    except.EArithmeticOverflow._0 = address;

    termina__shared__except__raise(except);

}

void termina__except__division_by_zero(
    const size_t address) {

    Exception except;
    except._variant = Exception__EDivisionByZero;
    except.EDivisionByZero._0 = address;

    termina__shared__except__raise(except);

}

void termina__except__array_index_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t index) {

    Exception except;
    except._variant = Exception__EArrayIndexOutOfBounds;
    except.EArrayIndexOutOfBounds._0 = address;
    except.EArrayIndexOutOfBounds._1 = array_size;
    except.EArrayIndexOutOfBounds._2 = index;

    termina__shared__except__raise(except);

}

void termina__except__array_slice_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t upper_bound) {

    Exception except;
    except._variant = Exception__EArraySliceOutOfBounds;
    except.EArraySliceOutOfBounds._0 = address;
    except.EArraySliceOutOfBounds._1 = array_size;
    except.EArraySliceOutOfBounds._2 = upper_bound;

    termina__shared__except__raise(except);

}

void termina__except__array_slice_negative_range(
    const size_t address,
    const size_t lower_bound,
    const size_t upper_bound) {

    Exception except;
    except._variant = Exception__EArraySliceNegativeRange;
    except.EArraySliceNegativeRange._0 = address;
    except.EArraySliceNegativeRange._1 = lower_bound;
    except.EArraySliceNegativeRange._2 = upper_bound;

    termina__shared__except__raise(except);

}

void termina__except__array_slice_invalid_range(
    const size_t address,
    const size_t expected_size,
    const size_t lower_bound,
    const size_t upper_bound) {

    Exception except;
    except._variant = Exception__EArraySliceInvalidRange;
    except.EArraySliceInvalidRange._0 = address;
    except.EArraySliceInvalidRange._1 = expected_size;
    except.EArraySliceInvalidRange._2 = lower_bound;
    except.EArraySliceInvalidRange._3 = upper_bound;

    termina__shared__except__raise(except);

}

void termina__except__action_failure(
    const ExceptSource source,
    const size_t sink_port_id,
    const int32_t error_code) {

    Exception except;
    except._variant = Exception__EActionFailure;
    except.EActionFailure._0 = source;
    except.EActionFailure._1 = sink_port_id;
    except.EActionFailure._2 = error_code;

    termina__shared__except__raise(except);

}

void termina__shared__except__handler_failure(const termina__id_t handler_id,
                                              const int32_t error_code) {

    ExceptSource source;
    source._variant = ExceptSource__Handler;
    source.Handler._0 = handler_id;

    termina__except__action_failure(source, 0U, error_code);

}

void termina__except__msg_queue_send_error(
    const size_t msg_queue_id,
    const termina__error_code_t error_code) {

    Exception except;
    except._variant = Exception__EMsgQueueSendError;
    except.EMsgQueueSendError._0 = msg_queue_id;
    except.EMsgQueueSendError._1 = (int32_t)error_code;

    termina__shared__except__raise(except);

}

void termina__except__msg_queue_recv_error(
    const size_t msg_queue_id,
    const termina__error_code_t error_code) {

    Exception except;
    except._variant = Exception__EMsgQueueRecvError;
    except.EMsgQueueRecvError._0 = msg_queue_id;
    except.EMsgQueueRecvError._1 = (int32_t)error_code;

    termina__shared__except__raise(except);

}

void termina__except__runtime_failure(
    const termina__runtime_operation_t operation,
    const termina__error_code_t error_code) {

    Exception except;
    except._variant = Exception__ERuntimeFailure;
    except.ERuntimeFailure._0 = (uint32_t)operation;
    except.ERuntimeFailure._1 = (int32_t)error_code;

    termina__shared__except__raise(except);

}

void termina__except__processor_fault(
    const uint32_t kind,
    const uint32_t status,
    const size_t pc,
    const size_t address) {

    Exception except;
    except._variant = Exception__EProcessorFault;
    except.EProcessorFault._0 = kind;
    except.EProcessorFault._1 = status;
    except.EProcessorFault._2 = pc;
    except.EProcessorFault._3 = address;

    termina__shared__except__raise(except);

}

void termina__except__kernel_failure(
    const uint32_t source,
    const size_t code) {

    Exception except;
    except._variant = Exception__EKernelFailure;
    except.EKernelFailure._0 = source;
    except.EKernelFailure._1 = code;

    termina__shared__except__raise(except);

}

void termina__except__stack_overflow(
    const termina__id_t task_id) {

    Exception except;
    except._variant = Exception__EStackOverflow;
    except.EStackOverflow._0 = task_id;

    termina__shared__except__raise(except);

}
