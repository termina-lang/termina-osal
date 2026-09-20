
#include <termina.h>
#include <termina/shared/except.h>

#include <inttypes.h>

#include <FreeRTOS.h>

void termina__os_except__init_emitter(void) {
    
    // Nothing to do for FreeRTOS
    return;
    
}

void termina__except__shift_amount_out_of_bounds(
    const size_t address,
    const size_t width,
    const size_t amount) {

    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EShiftAmountOutOfBounds;
        except.EShiftAmountOutOfBounds._0 = address;
        except.EShiftAmountOutOfBounds._1 = width;
        except.EShiftAmountOutOfBounds._2 = amount;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__array_index_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t index) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EArrayIndexOutOfBounds;
        except.EArrayIndexOutOfBounds._0 = address;
        except.EArrayIndexOutOfBounds._1 = array_size;
        except.EArrayIndexOutOfBounds._2 = index;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__array_slice_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EArraySliceOutOfBounds;
        except.EArraySliceOutOfBounds._0 = address;
        except.EArraySliceOutOfBounds._1 = array_size;
        except.EArraySliceOutOfBounds._2 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__array_slice_negative_range(
    const size_t address,
    const size_t lower_bound,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EArraySliceNegativeRange;
        except.EArraySliceNegativeRange._0 = address;
        except.EArraySliceNegativeRange._1 = lower_bound;
        except.EArraySliceNegativeRange._2 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__array_slice_invalid_range(
    const size_t address,
    const size_t expected_size,
    const size_t lower_bound,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EArraySliceInvalidRange;
        except.EArraySliceInvalidRange._0 = address;
        except.EArraySliceInvalidRange._1 = expected_size;
        except.EArraySliceInvalidRange._2 = lower_bound;
        except.EArraySliceInvalidRange._3 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__action_failure(
    const ExceptSource source,
    const size_t sink_port_id,
    const int32_t status) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EActionFailure;
        except.EActionFailure._0 = source;
        except.EActionFailure._1 = sink_port_id;
        except.EActionFailure._2 = status;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__msg_queue_send_error(
    const size_t msg_queue_id,
    const int32_t error_code) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EMsgQueueSendError;
        except.EMsgQueueSendError._0 = msg_queue_id;
        except.EMsgQueueSendError._1 = error_code;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void termina__except__msg_queue_recv_error(
    const size_t msg_queue_id,
    const int32_t error_code) {
    
    if (system_except.handler_action == NULL) {

        termina__exec__reboot();

    } else {

        Exception except;
        except._variant = Exception__EMsgQueueRecvError;
        except.EMsgQueueRecvError._0 = msg_queue_id;
        except.EMsgQueueRecvError._1 = error_code;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}
