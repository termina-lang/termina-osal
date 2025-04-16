
#include <termina.h>

size_t __termina_array__index(size_t array_size, size_t index) {

    if (index >= array_size) {

        __termina_exec__shutdown();

    }

    return index;

}

size_t __termina_array__slice(size_t array_size, size_t slice_size, size_t lower, size_t upper) {

    if (upper >= array_size) {

        __termina_exec__shutdown();

    } else if  (lower > upper) {

        __termina_exec__shutdown();

    } else if (upper - lower != slice_size) {

        __termina_exec__shutdown();

    } else {


    }

    return lower;

}
