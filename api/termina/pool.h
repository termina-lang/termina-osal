/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Interface of the memory pools.
 */

#ifndef TERMINA__POOL_H__
#define TERMINA__POOL_H__

#include <termina/types.h>

/**
 * @brief Alignment of the memory area of a pool and of each of its blocks.
 *
 * It is the strictest alignment that the platform requires for a basic type,
 * so that a block can hold an object of any type.
 */
#define TERMINA__POOL__BLOCK_ALIGNMENT _Alignof(max_align_t)

/**
 * @brief Minimum size of a block, which holds the address of the next free
 *        block while the block is free.
 */
#define TERMINA__POOL__MINIMUM_BLOCK_SIZE sizeof(uintptr_t)

/**
 * @brief Size of a block that holds an element of the given size.
 *
 * @param[in] size  Size of the element in bytes, as returned by `sizeof`.
 *
 * @return The size, or the minimum block size if it is larger, rounded up to
 *         a multiple of the block alignment.
 */
#define termina__pool__block_size(size) \
	(((((size) > TERMINA__POOL__MINIMUM_BLOCK_SIZE ? (size) : \
		TERMINA__POOL__MINIMUM_BLOCK_SIZE) + \
		(TERMINA__POOL__BLOCK_ALIGNMENT - 1U)) / \
		TERMINA__POOL__BLOCK_ALIGNMENT) * TERMINA__POOL__BLOCK_ALIGNMENT)

/**
 * @brief Initializes a memory pool.
 *
 * @param[in]  self              Pointer to the pool object, of type
 *                               `termina__pool_t`.
 * @param[in]  p_memory_area     Pointer to the memory area that holds the
 *                               blocks.
 * @param[in]  memory_area_size  Size of the memory area in bytes.
 * @param[in]  block_size        Size of the elements of the pool in bytes.
 * @param[out] status            Status of the operation:
 *                               `termina__error__none`, or
 *                               `termina__error__pool_init` if the identifier,
 *                               the block size, the alignment or the size of
 *                               the memory area is not valid.
 */
void termina__pool__init(void * const self,
                          void * const p_memory_area, 
                          size_t memory_area_size, 
                          size_t block_size, 
                          termina__error_code_t * const status);

/**
 * @brief Allocates a block from a pool.
 *
 * If the identifier of the pool is not valid, the function raises
 * `ERuntimeFailure`.
 *
 * @param[in]  termina__ev    Pointer to the event that is being processed.
 * @param[in]  termina__this  Pointer to the pool object.
 * @param[out] opt            The allocated block, or `None` if the pool has no
 *                            free blocks.
 */
void termina__pool__alloc(const termina__event_t * const termina__ev,
                           void * const termina__this,
                           Option__box * const opt);

/**
 * @brief Returns a block to its pool.
 *
 * If the identifier of the pool is not valid, or the address is not the start
 * of a block of the pool, the function raises `ERuntimeFailure`.
 *
 * @param[in] termina__ev    Pointer to the event that is being processed.
 * @param[in] termina__this  Pointer to the pool object.
 * @param[in] element        Box that holds the block to free.
 */
void termina__pool__free(const termina__event_t * const termina__ev,
                          void * const termina__this, 
                          termina__box_t element);

/**
 * @brief Length of the memory area of a pool, counted in elements of
 *        `max_align_t`.
 *
 * The memory area is declared as an array of `max_align_t`, which places it
 * at an address with the alignment of the blocks.
 *
 * @param[in] size       Size of each element in bytes, as returned by
 *                       `sizeof`.
 * @param[in] dimension  Number of elements of the pool.
 *
 * @return The number of `max_align_t` elements of the memory area of the pool.
 */
#define termina__pool__area_length(size, dimension) \
	(((termina__pool__block_size(size) * (dimension)) + \
		(sizeof(max_align_t) - 1U)) / sizeof(max_align_t))


#endif // TERMINA__POOL_H__
