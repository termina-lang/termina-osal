#ifndef __TERMINA__ARRAY_H__
#define __TERMINA__ARRAY_H__

#include <termina/types.h>

/**
 * \brief Checks an array index against its size.
 *
 * @param[in] array_size  The size of the array.
 * @param[in] index       The value of the index.
 *
 * @return The index if it is within limits. Otherwise, it will trigger an error.
 */
size_t __termina_array__index(size_t array_size, size_t index);

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
size_t __termina_array__slice(size_t array_size, size_t slice_size, size_t lower, size_t upper);


#endif // __TERMINA__ARRAY_H__
