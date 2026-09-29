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

/**
 * \brief Carries out a signed operation, checking that its result is
 *        representable in the type of its operands.
 *
 * The i8 and i16 operations are carried out in int32_t, where none of them can
 * overflow whatever the width of int, and their result is checked against the
 * range of the type. The i32 and i64 operations check their operands before
 * they are carried out. The division and the remainder also check that the
 * divisor is not zero. The remainder of the minimum value by -1 is zero, which
 * is representable, even though C leaves it undefined.
 *
 * @param[in] a  The left operand.
 * @param[in] b  The right operand.
 *
 * @return The result of the operation. If it is not representable, or the
 *         divisor is zero, it will trigger an error.
 */
int8_t termina__check__add_i8(int8_t a, int8_t b);
int8_t termina__check__sub_i8(int8_t a, int8_t b);
int8_t termina__check__mul_i8(int8_t a, int8_t b);
int8_t termina__check__div_i8(int8_t a, int8_t b);
int8_t termina__check__mod_i8(int8_t a, int8_t b);
int16_t termina__check__add_i16(int16_t a, int16_t b);
int16_t termina__check__sub_i16(int16_t a, int16_t b);
int16_t termina__check__mul_i16(int16_t a, int16_t b);
int16_t termina__check__div_i16(int16_t a, int16_t b);
int16_t termina__check__mod_i16(int16_t a, int16_t b);
int32_t termina__check__add_i32(int32_t a, int32_t b);
int32_t termina__check__sub_i32(int32_t a, int32_t b);
int32_t termina__check__mul_i32(int32_t a, int32_t b);
int32_t termina__check__div_i32(int32_t a, int32_t b);
int32_t termina__check__mod_i32(int32_t a, int32_t b);
int64_t termina__check__add_i64(int64_t a, int64_t b);
int64_t termina__check__sub_i64(int64_t a, int64_t b);
int64_t termina__check__mul_i64(int64_t a, int64_t b);
int64_t termina__check__div_i64(int64_t a, int64_t b);
int64_t termina__check__mod_i64(int64_t a, int64_t b);

/**
 * \brief Checks that the divisor of an unsigned division or remainder is not
 *        zero.
 *
 * @param[in] divisor  The value of the divisor.
 *
 * @return The divisor if it is not zero. Otherwise, it will trigger an error.
 */
uint8_t termina__check__divisor_u8(uint8_t divisor);
uint16_t termina__check__divisor_u16(uint16_t divisor);
uint32_t termina__check__divisor_u32(uint32_t divisor);
uint64_t termina__check__divisor_u64(uint64_t divisor);
size_t termina__check__divisor_usize(size_t divisor);

#endif // TERMINA__CHECK_H__
