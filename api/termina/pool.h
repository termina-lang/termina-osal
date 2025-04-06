#ifndef __TERMINA__POOL_H__
#define __TERMINA__POOL_H__

#include "config.h"

#include <termina/types.h>

#define __TERMINA_POOL_MINIMUM_BLOCK_SIZE sizeof(uintptr_t)

/**
 * \brief Initializes a memory pool.
 *
 * @param[in]  pool              pointer to the pool to initialize.
 * @param[in]  p_memory_area     pointer to the memory that will be used to
 *                               allocate the blocks.
 * @param[in]  memory_area_size  size of the memory area.
 * @param[in]  block_size        size of the blocks of the pool.
 * @param[in]  mutex_id          identifier of the mutex that shall be used to
 *                               protect the pool
 * @param[out] status            Success if the pool was initialized
 *                               successfully or an error otherwise.
 */
void __termina_pool__init(void * const pool, 
                          void * const p_memory_area, 
                          size_t memory_area_size, 
                          size_t block_size, 
                          __termina_id_t mutex_id,
                          Status * const status);

/**
 * \brief Allocates an element from a given pool.
 *
 * @param[in] pool  pointer to the pool from which the element will be
 *                  allocated.
 * @param[out] opt  pointer to the option variable that will store the valid
 *                  allocated element.
 *
 */
void __termina_pool__alloc(void * const pool,
                           __option_box_t * const opt);
void __termina_pool__alloc__mutex_lock(void * const pool,
                                       __option_box_t * const opt);
void __termina_pool__alloc__task_lock(void * const pool,
                                      __option_box_t * const opt);
void __termina_pool__alloc__event_lock(void * const pool,
                                       __option_box_t * const opt);

/**
 * \brief Deallocates an element from a given pool.
 *
 * @param[in] pool     pointer to the pool from which the element will be
 *                     deallocated (freed).
 * @param[in] element  dynamic element to deallocate.
 */
void __termina_pool__free(void * const pool, 
                          __termina_box_t element);
void __termina_pool__free__mutex_lock(void * const pool, 
                                      __termina_box_t element);
void __termina_pool__free__task_lock(void * const pool, 
                                     __termina_box_t element);
void __termina_pool__free__event_lock(void * const pool, 
                                      __termina_box_t element);

/**
 * \brief Returns the size of the memory area for a given pool.
 *
 * @param[in] size       size of each element in bytes (as retured by the sizeof
 *                       operator.
 * @param[in] dimension  number of elements of the pool.
 *
 * @return  size of the memory area of the pool.
 */
#define __termina_pool__size(size, dimension) \
	((size) + (__TERMINA_POOL_MINIMUM_BLOCK_SIZE - \
		((size) % __TERMINA_POOL_MINIMUM_BLOCK_SIZE)) * (dimension))


#endif // __TERMINA__POOL_H__
