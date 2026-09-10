#ifndef __TERMINA__SHIFT_H__
#define __TERMINA__SHIFT_H__

#include <termina/types.h>

/**
 * \brief Checks a shift amount against the bit width of the shifted type.
 *
 * @param[in] width   The bit width of the left operand's type.
 * @param[in] amount  The value of the shift amount.
 *
 * @return The amount if it is strictly less than the width. Otherwise, it will trigger an error.
 */
size_t __termina_shift__amount(size_t width, size_t amount);


#endif // __TERMINA__SHIFT_H__
