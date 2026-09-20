#ifndef TERMINA__CHECK_H__
#define TERMINA__CHECK_H__

#include <termina/types.h>

/**
 * \brief Checks an array index against its size.
 *
 * @param[in] array_size  The size of the array.
 * @param[in] index       The value of the index.
 *
 * @return The index if it is within limits. Otherwise, it will trigger an error.
 */
size_t termina__check__array_index(size_t array_size, size_t index);

/**
 * \brief Checks the parameters of an array slice against its size.
 *
 * @param[in] array_size  The size of the original array.
 * @param[in] slice_size  The expected size of the slice.
 * @param[in] lower       The value of the lower bound.
 * @param[in] upper       The value of the lower bound.
 *
 * @return The lower bound index if it is within limits. Otherwise, it will trigger an error.
 */
size_t termina__check__array_slice(size_t array_size, size_t slice_size, size_t lower, size_t upper);


/**
 * \brief Checks a shift amount against the bit width of the shifted type.
 *
 * @param[in] width   The bit width of the left operand's type.
 * @param[in] amount  The value of the shift amount.
 *
 * @return The amount if it is strictly less than the width. Otherwise, it will trigger an error.
 */
size_t termina__check__shift_amount(size_t width, size_t amount);

#endif // TERMINA__CHECK_H__
