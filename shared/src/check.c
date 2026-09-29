
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

// The i8 and i16 operations are carried out in int32_t, where none of them can
// overflow whatever the width of int, and their result is checked against the
// range of the type. The address is the one of the caller of the public
// function, which it takes and passes on.

static int32_t termina__shared__check__fit(int32_t value, int32_t min, int32_t max,
                                           size_t address) {

    int32_t result = 0;

    if ((value < min) || (value > max)) {

        termina__except__arithmetic_overflow(address);

    } else {

        result = value;

    }

    return result;

}

static int32_t termina__shared__check__quotient(int32_t a, int32_t b, size_t address) {

    int32_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(address);

    } else {

        result = a / b;

    }

    return result;

}

static int32_t termina__shared__check__remainder(int32_t a, int32_t b, size_t address) {

    int32_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(address);

    } else {

        result = a % b;

    }

    return result;

}

int8_t termina__check__add_i8(int8_t a, int8_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int8_t)termina__shared__check__fit((int32_t)a + (int32_t)b,
                                               INT8_MIN, INT8_MAX, address);

}

int8_t termina__check__sub_i8(int8_t a, int8_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int8_t)termina__shared__check__fit((int32_t)a - (int32_t)b,
                                               INT8_MIN, INT8_MAX, address);

}

int8_t termina__check__mul_i8(int8_t a, int8_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int8_t)termina__shared__check__fit((int32_t)a * (int32_t)b,
                                               INT8_MIN, INT8_MAX, address);

}

int8_t termina__check__div_i8(int8_t a, int8_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int8_t)termina__shared__check__fit(
        termina__shared__check__quotient((int32_t)a, (int32_t)b, address),
        INT8_MIN, INT8_MAX, address);

}

int8_t termina__check__mod_i8(int8_t a, int8_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int8_t)termina__shared__check__remainder((int32_t)a, (int32_t)b, address);

}

int16_t termina__check__add_i16(int16_t a, int16_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int16_t)termina__shared__check__fit((int32_t)a + (int32_t)b,
                                                INT16_MIN, INT16_MAX, address);

}

int16_t termina__check__sub_i16(int16_t a, int16_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int16_t)termina__shared__check__fit((int32_t)a - (int32_t)b,
                                                INT16_MIN, INT16_MAX, address);

}

int16_t termina__check__mul_i16(int16_t a, int16_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int16_t)termina__shared__check__fit((int32_t)a * (int32_t)b,
                                                INT16_MIN, INT16_MAX, address);

}

int16_t termina__check__div_i16(int16_t a, int16_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int16_t)termina__shared__check__fit(
        termina__shared__check__quotient((int32_t)a, (int32_t)b, address),
        INT16_MIN, INT16_MAX, address);

}

int16_t termina__check__mod_i16(int16_t a, int16_t b) {

    size_t address = (uintptr_t)__builtin_return_address(0);

    return (int16_t)termina__shared__check__remainder((int32_t)a, (int32_t)b, address);

}

// The preconditions of the i32 and i64 operations are the ones of CERT INT32-C
// and INT33-C: each tests the operands against the limits of the type before
// the operation, so the operation is only carried out when its result is
// representable.

int32_t termina__check__add_i32(int32_t a, int32_t b) {

    int32_t result = 0;

    if (((b > 0) && (a > (INT32_MAX - b))) || ((b < 0) && (a < (INT32_MIN - b)))) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a + b;

    }

    return result;

}

int32_t termina__check__sub_i32(int32_t a, int32_t b) {

    int32_t result = 0;

    if (((b > 0) && (a < (INT32_MIN + b))) || ((b < 0) && (a > (INT32_MAX + b)))) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a - b;

    }

    return result;

}

int32_t termina__check__mul_i32(int32_t a, int32_t b) {

    int32_t result = 0;
    _Bool overflow = false;

    if (a > 0) {
        if (b > 0) {
            overflow = a > (INT32_MAX / b);
        } else {
            overflow = b < (INT32_MIN / a);
        }
    } else {
        if (b > 0) {
            overflow = a < (INT32_MIN / b);
        } else {
            overflow = (a != 0) && (b < (INT32_MAX / a));
        }
    }

    if (overflow) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a * b;

    }

    return result;

}

int32_t termina__check__div_i32(int32_t a, int32_t b) {

    int32_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    } else if ((a == INT32_MIN) && (b == -1)) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a / b;

    }

    return result;

}

int32_t termina__check__mod_i32(int32_t a, int32_t b) {

    int32_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    } else if (b != -1) {

        result = a % b;

    } else {

        // The remainder by -1 is always zero; C leaves the one of INT32_MIN
        // undefined, since the quotient is not representable.

    }

    return result;

}

int64_t termina__check__add_i64(int64_t a, int64_t b) {

    int64_t result = 0;

    if (((b > 0) && (a > (INT64_MAX - b))) || ((b < 0) && (a < (INT64_MIN - b)))) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a + b;

    }

    return result;

}

int64_t termina__check__sub_i64(int64_t a, int64_t b) {

    int64_t result = 0;

    if (((b > 0) && (a < (INT64_MIN + b))) || ((b < 0) && (a > (INT64_MAX + b)))) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a - b;

    }

    return result;

}

int64_t termina__check__mul_i64(int64_t a, int64_t b) {

    int64_t result = 0;
    _Bool overflow = false;

    if (a > 0) {
        if (b > 0) {
            overflow = a > (INT64_MAX / b);
        } else {
            overflow = b < (INT64_MIN / a);
        }
    } else {
        if (b > 0) {
            overflow = a < (INT64_MIN / b);
        } else {
            overflow = (a != 0) && (b < (INT64_MAX / a));
        }
    }

    if (overflow) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a * b;

    }

    return result;

}

int64_t termina__check__div_i64(int64_t a, int64_t b) {

    int64_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    } else if ((a == INT64_MIN) && (b == -1)) {

        termina__except__arithmetic_overflow(
            (uintptr_t)__builtin_return_address(0));

    } else {

        result = a / b;

    }

    return result;

}

int64_t termina__check__mod_i64(int64_t a, int64_t b) {

    int64_t result = 0;

    if (b == 0) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    } else if (b != -1) {

        result = a % b;

    } else {

        // Same as termina__check__mod_i32.

    }

    return result;

}

uint8_t termina__check__divisor_u8(uint8_t divisor) {

    if (divisor == 0U) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    }

    return divisor;

}

uint16_t termina__check__divisor_u16(uint16_t divisor) {

    if (divisor == 0U) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    }

    return divisor;

}

uint32_t termina__check__divisor_u32(uint32_t divisor) {

    if (divisor == 0U) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    }

    return divisor;

}

uint64_t termina__check__divisor_u64(uint64_t divisor) {

    if (divisor == 0U) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    }

    return divisor;

}

size_t termina__check__divisor_usize(size_t divisor) {

    if (divisor == 0U) {

        termina__except__division_by_zero(
            (uintptr_t)__builtin_return_address(0));

    }

    return divisor;

}

size_t termina__check__shift_amount(size_t width, size_t amount) {

    if (amount >= width) {

        termina__except__shift_amount_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            width, amount);

    }

    return amount;

}
