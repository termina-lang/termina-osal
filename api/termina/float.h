#ifndef __TERMINA__FLOAT_H__
#define __TERMINA__FLOAT_H__

#include <stdint.h>
#include <string.h>
#include <float.h>

/**
 * \brief Type that implements the f32 IEEE-754 binary32 floating point type.
 *
 * C does not provide fixed-width floating point types, so f32 is mapped to the
 * float type. The static assertion below checks that, on the target toolchain,
 * float is an IEEE-754 binary32 number.
 */
typedef float float32_t;

/**
 * \brief Type that implements the f64 IEEE-754 binary64 floating point type.
 *
 * C does not provide fixed-width floating point types, so f64 is mapped to the
 * double type. The static assertion below checks that, on the target toolchain,
 * double is an IEEE-754 binary64 number.
 */
typedef double float64_t;

_Static_assert(sizeof(float32_t) == 4 && FLT_RADIX == 2 && FLT_MANT_DIG == 24,
               "Termina f32 requires an IEEE-754 binary32 float");
_Static_assert(sizeof(float64_t) == 8 && DBL_MANT_DIG == 53,
               "Termina f64 requires an IEEE-754 binary64 double");

/**
 * \brief Reinterpret the bits of a 32-bit float as an unsigned 32-bit integer.
 *
 * @param[in] value  the floating point value to reinterpret.
 * @return the IEEE-754 bit pattern of value.
 */
static inline uint32_t f32_to_bits(const float32_t value) {
    uint32_t bits;
    (void)memcpy(&bits, &value, sizeof(bits));
    return bits;
}

/**
 * \brief Reinterpret the bits of an unsigned 32-bit integer as a 32-bit float.
 *
 * @param[in] bits  the IEEE-754 bit pattern to reinterpret.
 * @return the floating point value with the given bit pattern.
 */
static inline float32_t f32_from_bits(const uint32_t bits) {
    float32_t value;
    (void)memcpy(&value, &bits, sizeof(value));
    return value;
}

/**
 * \brief Reinterpret the bits of a 64-bit float as an unsigned 64-bit integer.
 *
 * @param[in] value  the floating point value to reinterpret.
 * @return the IEEE-754 bit pattern of value.
 */
static inline uint64_t f64_to_bits(const float64_t value) {
    uint64_t bits;
    (void)memcpy(&bits, &value, sizeof(bits));
    return bits;
}

/**
 * \brief Reinterpret the bits of an unsigned 64-bit integer as a 64-bit float.
 *
 * @param[in] bits  the IEEE-754 bit pattern to reinterpret.
 * @return the floating point value with the given bit pattern.
 */
static inline float64_t f64_from_bits(const uint64_t bits) {
    float64_t value;
    (void)memcpy(&value, &bits, sizeof(value));
    return value;
}

#endif // __TERMINA__FLOAT_H__
