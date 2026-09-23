
#include <termina.h>
#include <termina/shared/except.h>

termina__emitter_system_except_t system_except;

void termina__except__init_emitter(void * const handler_object,
                                    const termina__system_except_action_t handler_action) {

    system_except.handler_object = handler_object;
    system_except.handler_action = handler_action;

    termina__os__except__init_emitter();

}

/**
 * \brief Raises an exception, which is the one path every exception takes.
 *
 * The handler of the application runs when one is registered, and the system
 * reboots afterwards either way: the exceptions this runtime raises are the
 * ones it cannot recover from, so the handler records the cause and the system
 * restarts. Every back-end behaves the same, and what is left of the operating
 * system is the entry, which stops whatever could run in the middle.
 */
static void termina__shared__except__raise(const Exception except) {

    // Set before the handler runs and never cleared: an exception raised while
    // the handler is running is a failure of the handler itself, and the system
    // reboots without calling it a second time. The read and the write need no
    // atomic, because the entry above has already disabled the interrupts of
    // the processor and nothing else runs between them.
    static _Bool servicing = false;

    termina__os__except__enter();

    if ((NULL != system_except.handler_action) && (!servicing)) {

        servicing = true;

        system_except.handler_action(system_except.handler_object, except);

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
    const int32_t status) {

    Exception except;
    except._variant = Exception__EActionFailure;
    except.EActionFailure._0 = source;
    except.EActionFailure._1 = sink_port_id;
    except.EActionFailure._2 = status;

    termina__shared__except__raise(except);

}

void termina__except__msg_queue_send_error(
    const size_t msg_queue_id,
    const int32_t error_code) {

    Exception except;
    except._variant = Exception__EMsgQueueSendError;
    except.EMsgQueueSendError._0 = msg_queue_id;
    except.EMsgQueueSendError._1 = error_code;

    termina__shared__except__raise(except);

}

void termina__except__msg_queue_recv_error(
    const size_t msg_queue_id,
    const int32_t error_code) {

    Exception except;
    except._variant = Exception__EMsgQueueRecvError;
    except.EMsgQueueRecvError._0 = msg_queue_id;
    except.EMsgQueueRecvError._1 = error_code;

    termina__shared__except__raise(except);

}
