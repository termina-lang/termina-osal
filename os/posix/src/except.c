
#include <termina.h>
#include <termina/shared/except.h>
#include <termina/os/posix/signal.h>

#include <stdio.h>

void __termina_os_except__init_emitter(void) {
    
    // Nothing to do for POSIX
    return;
    
}

void __termina_except__shift_amount_out_of_bounds(
    const size_t address,
    const size_t width,
    const size_t amount) {

    __posix_signal__disable();

    if (system_except.handler_action == NULL) {

        printf("\033[1;31m[runtime error]\033[0m (0x%zu) shift amount out of bounds => width = %zu; amount = %zu\n", address, width, amount);
        __termina_exec__reboot();

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
        except._variant = Exception__EArrayIndexOutOfBounds;
        except.EArrayIndexOutOfBounds._0 = address;
        except.EArrayIndexOutOfBounds._1 = array_size;
        except.EArrayIndexOutOfBounds._2 = index;

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
        except._variant = Exception__EArraySliceOutOfBounds;
        except.EArraySliceOutOfBounds._0 = address;
        except.EArraySliceOutOfBounds._1 = array_size;
        except.EArraySliceOutOfBounds._2 = upper_bound;

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
        except._variant = Exception__EArraySliceNegativeRange;
        except.EArraySliceNegativeRange._0 = address;
        except.EArraySliceNegativeRange._1 = lower_bound;
        except.EArraySliceNegativeRange._2 = upper_bound;

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
        except._variant = Exception__EArraySliceInvalidRange;
        except.EArraySliceInvalidRange._0 = address;
        except.EArraySliceInvalidRange._1 = expected_size;
        except.EArraySliceInvalidRange._2 = lower_bound;
        except.EArraySliceInvalidRange._3 = upper_bound;

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

        if (source._variant == ExceptSource__Task) {
            printf("\033[1;31m[runtime error]\033[0m action failure => task = %zu; id = %zu; status = %d\n", source.Task._0, sink_port_id, status);
        } else {
            printf("\033[1;31m[runtime error]\033[0m action failure => handler = %zu; id = %zu; status = %d\n", source.Handler._0, sink_port_id, status);
        }
        __termina_exec__reboot();

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
        except._variant = Exception__EMsgQueueSendError;
        except.EMsgQueueSendError._0 = msg_queue_id;
        except.EMsgQueueSendError._1 = error_code;

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
        except._variant = Exception__EMsgQueueRecvError;
        except.EMsgQueueRecvError._0 = msg_queue_id;
        except.EMsgQueueRecvError._1 = error_code;

        system_except.handler_action(
            (void *)&system_except.handler_action, except);

    }

}