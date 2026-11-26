/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Run-time checks of array indexes, slices, shifts and integer
 *        arithmetic that the generated code calls.
 */

#ifndef TERMINA__CHECK_H__
#define TERMINA__CHECK_H__

#include <termina/types.h>

/**
 * @brief Checks an array index against the size of the array.
 *
 * @param[in] array_size  Size of the array.
 * @param[in] index       Value of the index.
 *
 * @return The index. If it is not below the size, the function raises
 *         `EArrayIndexOutOfBounds` and does not return.
 */
size_t termina__check__array_index(size_t array_size, size_t index);

/**
 * @brief Checks the bounds of an array slice against the size of the array.
 *
 * @param[in] array_size  Size of the original array.
 * @param[in] slice_size  Expected size of the slice.
 * @param[in] lower       Lower bound of the slice.
 * @param[in] upper       Upper bound of the slice.
 *
 * @return The lower bound. If the bounds are not valid, the function raises
 *         `EArraySliceOutOfBounds`, `EArraySliceNegativeRange` or
 *         `EArraySliceInvalidRange` and does not return.
 */
size_t termina__check__array_slice(size_t array_size, size_t slice_size, size_t lower, size_t upper);


/**
 * @brief Checks a shift amount against the bit width of the shifted type.
 *
 * @param[in] width   Bit width of the type of the left operand.
 * @param[in] amount  Value of the shift amount.
 *
 * @return The amount. If it is not below the width, the function raises
 *         `EShiftAmountOutOfBounds` and does not return.
 */
size_t termina__check__shift_amount(size_t width, size_t amount);

/**
 * @brief Adds two `int8_t` values, checking that the result is representable.
 *
 * The i8 and i16 operations are carried out in `int32_t`, where none of them
 * can overflow whatever the width of `int`, and their result is checked
 * against the range of the type. The i32 and i64 operations check their
 * operands before they are carried out. The division and the remainder also
 * check that the divisor is not zero. The remainder of the minimum value by -1
 * is zero, which is representable, although C leaves it undefined.
 *
 * @param[in] a  Left operand.
 * @param[in] b  Right operand.
 *
 * @return The result of the operation. If it is not representable, the
 *         function raises `EArithmeticOverflow`, and if the divisor is zero,
 *         `EDivisionByZero`; in both cases it does not return.
 */
int8_t termina__check__add_i8(int8_t a, int8_t b);
/**
 * @brief Subtracts two `int8_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int8_t termina__check__sub_i8(int8_t a, int8_t b);
/**
 * @brief Multiplies two `int8_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int8_t termina__check__mul_i8(int8_t a, int8_t b);
/**
 * @brief Divides two `int8_t` values, checking the divisor and the result.
 *
 * @copydetails termina__check__add_i8
 */
int8_t termina__check__div_i8(int8_t a, int8_t b);
/**
 * @brief Computes the remainder of two `int8_t` values, checking the divisor.
 *
 * @copydetails termina__check__add_i8
 */
int8_t termina__check__mod_i8(int8_t a, int8_t b);
/**
 * @brief Adds two `int16_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int16_t termina__check__add_i16(int16_t a, int16_t b);
/**
 * @brief Subtracts two `int16_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int16_t termina__check__sub_i16(int16_t a, int16_t b);
/**
 * @brief Multiplies two `int16_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int16_t termina__check__mul_i16(int16_t a, int16_t b);
/**
 * @brief Divides two `int16_t` values, checking the divisor and the result.
 *
 * @copydetails termina__check__add_i8
 */
int16_t termina__check__div_i16(int16_t a, int16_t b);
/**
 * @brief Computes the remainder of two `int16_t` values, checking the divisor.
 *
 * @copydetails termina__check__add_i8
 */
int16_t termina__check__mod_i16(int16_t a, int16_t b);
/**
 * @brief Adds two `int32_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int32_t termina__check__add_i32(int32_t a, int32_t b);
/**
 * @brief Subtracts two `int32_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int32_t termina__check__sub_i32(int32_t a, int32_t b);
/**
 * @brief Multiplies two `int32_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int32_t termina__check__mul_i32(int32_t a, int32_t b);
/**
 * @brief Divides two `int32_t` values, checking the divisor and the result.
 *
 * @copydetails termina__check__add_i8
 */
int32_t termina__check__div_i32(int32_t a, int32_t b);
/**
 * @brief Computes the remainder of two `int32_t` values, checking the divisor.
 *
 * @copydetails termina__check__add_i8
 */
int32_t termina__check__mod_i32(int32_t a, int32_t b);
/**
 * @brief Adds two `int64_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int64_t termina__check__add_i64(int64_t a, int64_t b);
/**
 * @brief Subtracts two `int64_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int64_t termina__check__sub_i64(int64_t a, int64_t b);
/**
 * @brief Multiplies two `int64_t` values, checking that the result is
 *        representable.
 *
 * @copydetails termina__check__add_i8
 */
int64_t termina__check__mul_i64(int64_t a, int64_t b);
/**
 * @brief Divides two `int64_t` values, checking the divisor and the result.
 *
 * @copydetails termina__check__add_i8
 */
int64_t termina__check__div_i64(int64_t a, int64_t b);
/**
 * @brief Computes the remainder of two `int64_t` values, checking the divisor.
 *
 * @copydetails termina__check__add_i8
 */
int64_t termina__check__mod_i64(int64_t a, int64_t b);

/**
 * @brief Checks that the `uint8_t` divisor of an unsigned division or
 *        remainder is not zero.
 *
 * @param[in] divisor  Value of the divisor.
 *
 * @return The divisor. If it is zero, the function raises `EDivisionByZero`
 *         and does not return.
 */
uint8_t termina__check__divisor_u8(uint8_t divisor);
/**
 * @brief Checks that the `uint16_t` divisor of an unsigned division or
 *        remainder is not zero.
 *
 * @copydetails termina__check__divisor_u8
 */
uint16_t termina__check__divisor_u16(uint16_t divisor);
/**
 * @brief Checks that the `uint32_t` divisor of an unsigned division or
 *        remainder is not zero.
 *
 * @copydetails termina__check__divisor_u8
 */
uint32_t termina__check__divisor_u32(uint32_t divisor);
/**
 * @brief Checks that the `uint64_t` divisor of an unsigned division or
 *        remainder is not zero.
 *
 * @copydetails termina__check__divisor_u8
 */
uint64_t termina__check__divisor_u64(uint64_t divisor);
/**
 * @brief Checks that the `size_t` divisor of an unsigned division or
 *        remainder is not zero.
 *
 * @copydetails termina__check__divisor_u8
 */
size_t termina__check__divisor_usize(size_t divisor);

#endif // TERMINA__CHECK_H__
