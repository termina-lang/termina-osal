#ifndef TERMINA__POOL_H__
#define TERMINA__POOL_H__

#include "config.h"

#include <termina/types.h>

/**
 * \brief Alignment of the memory area of a pool and of each of its blocks.
 *
 * It is the strictest alignment that the platform requires for a basic type,
 * so that a block can hold an object of any type.
 */
#define TERMINA__POOL__BLOCK_ALIGNMENT _Alignof(max_align_t)

/**
 * \brief Minimum size of a block, which holds the address of the next free
 * block while the block is free.
 */
#define TERMINA__POOL__MINIMUM_BLOCK_SIZE sizeof(uintptr_t)

/**
 * \brief Size of a block that holds an element of the given size.
 *
 * @param[in] size  size of the element in bytes (as returned by the sizeof
 *                  operator).
 *
 * @return  the size, or the minimum block size if it is larger, rounded up to
 *          a multiple of the block alignment.
 */
#define termina__pool__block_size(size) \
	(((((size) > TERMINA__POOL__MINIMUM_BLOCK_SIZE ? (size) : \
		TERMINA__POOL__MINIMUM_BLOCK_SIZE) + \
		(TERMINA__POOL__BLOCK_ALIGNMENT - 1U)) / \
		TERMINA__POOL__BLOCK_ALIGNMENT) * TERMINA__POOL__BLOCK_ALIGNMENT)

/**
 * \brief Initializes a memory pool.
 *
 * @param[in]  pool              pointer to the pool to initialize.
 * @param[in]  p_memory_area     pointer to the memory that will be used to
 *                               allocate the blocks.
 * @param[in]  memory_area_size  size of the memory area.
 * @param[in]  block_size        size of the blocks of the pool.
 * @param[out] status            Success if the pool was initialized
 *                               successfully or an error otherwise.
 */
void termina__pool__init(void * const pool, 
                          void * const p_memory_area, 
                          size_t memory_area_size, 
                          size_t block_size, 
                          termina__error_code_t * const status);

/**
 * \brief Allocates an element from a given pool.
 *
 * @param [in] termina__ev   pointer to the event that is being processed when the
 *                    allocation is requested.
 * @param[in] termina__this  pointer to the pool from which the element will be
 *                    allocated.
 * @param[out] opt    pointer to the option variable that will store the valid
 *                    allocated element.
 *
 */
void termina__pool__alloc(const termina__event_t * const termina__ev,
                           void * const termina__this,
                           Option__box * const opt);

/**
 * \brief Deallocates an element from a given pool.
 *
 * @param [in] termina__ev    pointer to the event that is being processed when the
 *                     deallocation is requested.
 * @param[in] termina__this   pointer to the pool from which the element will be
 *                     deallocated (freed).
 * @param[in] element  dynamic element to deallocate.
 */
void termina__pool__free(const termina__event_t * const termina__ev,
                          void * const termina__this, 
                          termina__box_t element);

/**
 * \brief Returns the length of the memory area of a pool, counted in elements
 * of max_align_t.
 *
 * The memory area is declared as an array of max_align_t, which places it at
 * an address with the alignment of the blocks.
 *
 * @param[in] size       size of each element in bytes (as returned by the
 *                       sizeof operator).
 * @param[in] dimension  number of elements of the pool.
 *
 * @return  number of max_align_t elements of the memory area of the pool.
 */
#define termina__pool__area_length(size, dimension) \
	(((termina__pool__block_size(size) * (dimension)) + \
		(sizeof(max_align_t) - 1U)) / sizeof(max_align_t))


#endif // TERMINA__POOL_H__
