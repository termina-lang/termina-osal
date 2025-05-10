
#include <termina.h>
#include <termina/os/posix/signal.h>

#include <stdio.h>

void __termina_except__array_index_out_of_bounds(
    const size_t address,
    const size_t array_size,
    const size_t index) {
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m (0x%zu) array index out of bounds => array size = %zu; index = %zu\n", address, array_size, index);
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m (0x%zu) array slice out of bounds => array size = %zu; upper bound = %zu\n", 
                address, array_size, upper_bound);
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m (0x%zu) array slice negative range => lower bound = %zu; upper bound = %zu\n", 
                address, lower_bound, upper_bound);
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m (0x%zu) array slice invalid range =>  expected size = %zu, lower bound = %zu; upper bound = %zu\n",
                address, expected_size, lower_bound, upper_bound);
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        if (source.__variant == ExceptSource__Task) {
            printf("\033[1;31m[runtime error]\033[0m action failure => task = %zu; id = %zu; status = %d\n", source.Task.__0, sink_port_id, status);
        } else {
            printf("\033[1;31m[runtime error]\033[0m action failure => handler = %zu; id = %zu; status = %d\n", source.Handler.__0, sink_port_id, status);
        }
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m message queue send error => id = %zu; error code = %d\n", 
                msg_queue_id, error_code);
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
    
    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m message queue receive error => id = %zu; error code = %d\n", 
                msg_queue_id, error_code);
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