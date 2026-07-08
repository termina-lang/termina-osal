
#include <termina.h>

size_t __termina_shift__amount(size_t width, size_t amount) {

    if (amount >= width) {

        __termina_except__shift_amount_out_of_bounds(
            (uintptr_t)__builtin_return_address(0),
            width, amount);

    }

    return amount;

}
