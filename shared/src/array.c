
#include <termina.h>

size_t __termina_array__index(size_t array_size, size_t index) {

    if (index >= array_size) {

        __termina_except__array_index_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            array_size, index);

    }

    return index;

}

size_t __termina_array__slice(size_t array_size, size_t slice_size, size_t lower, size_t upper) {

    if (upper >= array_size) {

        __termina_except__array_slice_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            array_size, upper);

    } else if  (lower > upper) {

        __termina_except__array_slice_negative_range(
            (uintptr_t)__builtin_return_address(0),
            lower, upper);

    } else if (upper - lower != slice_size) {

        __termina_except__array_slice_invalid_range(
            (uintptr_t)__builtin_return_address(0),
            slice_size, lower, upper);

    } else {


    }

    return lower;

}
