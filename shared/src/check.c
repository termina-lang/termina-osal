
#include <termina.h>

size_t termina__check__array_index(size_t array_size, size_t index) {

    if (index >= array_size) {

        termina__except__array_index_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            array_size, index);

    }

    return index;

}

size_t termina__check__array_slice(size_t array_size, size_t slice_size, size_t lower, size_t upper) {

    if (upper > array_size) {

        termina__except__array_slice_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            array_size, upper);

    } else if  (lower > upper) {

        termina__except__array_slice_negative_range(
            (uintptr_t)__builtin_return_address(0),
            lower, upper);

    } else if (upper - lower != slice_size) {

        termina__except__array_slice_invalid_range(
            (uintptr_t)__builtin_return_address(0),
            slice_size, lower, upper);

    } else {


    }

    return lower;

}

size_t termina__check__shift_amount(size_t width, size_t amount) {

    if (amount >= width) {

        termina__except__shift_amount_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            width, amount);

    }

    return amount;

}
