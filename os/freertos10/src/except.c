
#include <termina.h>
#include <termina/shared/except.h>

#include <inttypes.h>

#include <FreeRTOS.h>

void __termina_os_except__init_emitter() {
    
    // Nothing to do for FreeRTOS
    return;
    
}

void __termina_except__array_index_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t index) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EArrayIndexOutOfBounds;
        except.EArrayIndexOutOfBounds.__0 = address;
        except.EArrayIndexOutOfBounds.__1 = array_size;
        except.EArrayIndexOutOfBounds.__2 = index;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__array_slice_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EArraySliceOutOfBounds;
        except.EArraySliceOutOfBounds.__0 = address;
        except.EArraySliceOutOfBounds.__1 = array_size;
        except.EArraySliceOutOfBounds.__2 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__array_slice_negative_range(
    const size_t address,
    const size_t lower_bound,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EArraySliceNegativeRange;
        except.EArraySliceNegativeRange.__0 = address;
        except.EArraySliceNegativeRange.__1 = lower_bound;
        except.EArraySliceNegativeRange.__2 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__array_slice_invalid_range(
    const size_t address,
    const size_t expected_size,
    const size_t lower_bound,
    const size_t upper_bound) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EArraySliceInvalidRange;
        except.EArraySliceInvalidRange.__0 = address;
        except.EArraySliceInvalidRange.__1 = expected_size;
        except.EArraySliceInvalidRange.__2 = lower_bound;
        except.EArraySliceInvalidRange.__3 = upper_bound;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__action_failure(
    const ExceptSource source,
    const size_t sink_port_id,
    const int32_t status) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EActionFailure;
        except.EActionFailure.__0 = source;
        except.EActionFailure.__1 = sink_port_id;
        except.EActionFailure.__2 = status;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__msg_queue_send_error(
    const size_t msg_queue_id,
    const int32_t error_code) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EMsgQueueSendError;
        except.EMsgQueueSendError.__0 = msg_queue_id;
        except.EMsgQueueSendError.__1 = error_code;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}

void __termina_except__msg_queue_recv_error(
    const size_t msg_queue_id,
    const int32_t error_code) {
    
    if (system_except.handler_action == NULL) {

        __termina_exec__reboot();

    } else {

        Exception except;
        except.__variant = Exception__EMsgQueueRecvError;
        except.EMsgQueueRecvError.__0 = msg_queue_id;
        except.EMsgQueueRecvError.__1 = error_code;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}
