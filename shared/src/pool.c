
/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Implementation of the memory pools.
 */

#include "config.h"

#include <termina.h>

#include <termina/shared/pool.h>

#include <stdbool.h>

/**
 * @brief Structure that implements a memory pool.
 */
typedef struct {

    //! Identifier of the pool.
    termina__id_t pool_id;

    //! Address of the memory area that stores the blocks.
    uintptr_t memory_area;

    //! Size of the memory area in bytes.
    size_t memory_area_size;

    //! Size of the data blocks.
    size_t block_size;

    //! Number of free blocks.
    size_t free_blocks;

    //! Address of the list of free blocks.
    uintptr_t free_blocks_list;

} termina__shared__pool_t;

#ifndef TERMINA__APP_CONFIG__POOLS
#error "config.h must define TERMINA__APP_CONFIG__POOLS"
#else
#if (TERMINA__APP_CONFIG__POOLS > 0)

/**
 * @brief Size of the pool object table.
 */
#define TERMINA__SHARED__POOL_TABLE_SIZE TERMINA__APP_CONFIG__POOLS

/**
 * @brief Checks whether a pool identifier is valid.
 *
 * @param[in] pool_id  Identifier of the pool.
 *
 * @return True if the identifier is less than the number of pools defined in
 *         the application, false otherwise.
 */
static inline bool termina__shared__pool__is_valid_id(const termina__id_t pool_id) {
    return (pool_id < TERMINA__APP_CONFIG__POOLS);
}

#else

// The application defines no pools. ISO C does not allow arrays of size zero,
// so the table keeps one unused element, and no identifier is valid.
#define TERMINA__SHARED__POOL_TABLE_SIZE 1U

static inline bool termina__shared__pool__is_valid_id(const termina__id_t pool_id) {
    (void)pool_id;
    return false;
}

#endif
#endif

static termina__shared__pool_t termina__shared__pool_object_table[TERMINA__SHARED__POOL_TABLE_SIZE];

void termina__pool__init(void * const self,
    void * const p_memory_area, 
    size_t memory_area_size, 
    size_t block_size, 
    termina__error_code_t * const status) {

    termina__id_t pool_id = ((termina__pool_t * const)self)->pool_id;

    *status = termina__error__none;

    if (!termina__shared__pool__is_valid_id(pool_id)) {

        *status = termina__error__pool_init;

    } else if ((0U == block_size)
               || (block_size > (SIZE_MAX - (TERMINA__POOL__BLOCK_ALIGNMENT - 1U)))) {

        // A block of size zero holds nothing, and a block this large cannot
        // be rounded up to a multiple of the block alignment.
        *status = termina__error__pool_init;

    } else if (((uintptr_t)p_memory_area % TERMINA__POOL__BLOCK_ALIGNMENT) != 0U) {

        // The blocks would not be aligned for every type.
        *status = termina__error__pool_init;

    } else if (memory_area_size < termina__pool__block_size(block_size)) {

        // The memory area does not hold a single block, and the list of free
        // blocks would be written outside of it.
        *status = termina__error__pool_init;

    } else {

        termina__shared__pool_t * pool =
            &termina__shared__pool_object_table[pool_id];

        // The pool object is set to zero byte by byte.

        for (size_t i = 0; i < sizeof(termina__shared__pool_t); i = i + 1) {

            *(((uint8_t *) pool) + i) = 0;

        }

        // The fields of the pool are set.

        pool->pool_id = pool_id;

        pool->memory_area = (uintptr_t)p_memory_area;

        pool->memory_area_size = memory_area_size;

        // A block size that is a multiple of the alignment keeps every block
        // aligned, since the memory area is.
        pool->block_size = termina__pool__block_size(block_size);

        // The list of free blocks begins at the start of the memory area.
        pool->free_blocks_list = pool->memory_area;

        // Every block of the memory area is free.
        pool->free_blocks = pool->memory_area_size / pool->block_size;

        uintptr_t ptr = pool->free_blocks_list;

        // Each block except the last one holds the address of the next block.
        for (size_t i = 0; i < (pool->free_blocks - 1); i = i + 1) {

            // The block holds the address of the next block.
            *(uintptr_t *)ptr = ptr + pool->block_size;

            // The pointer moves to the next block.
            ptr = ptr + pool->block_size;

        }

        // The last block holds a null address.
        *((uintptr_t *) ptr) = (uintptr_t)NULL;

    }

    return;

}

void * termina__shared__pool__take(const termina__id_t pool_id,
                                   termina__error_code_t * const status) {

    termina__shared__pool_t * pool = NULL;

    void * block = NULL;

    *status = termina__error__none;

    if (termina__shared__pool__is_valid_id(pool_id)) {

        pool = &termina__shared__pool_object_table[pool_id];

    } else {

        *status = termina__error__invalid_id;

    }

    // A block is taken only from a valid pool that has free blocks.
    if ((NULL != pool) && (pool->free_blocks > 0)) {

        // The first free block of the list is taken.
        block = (void *)pool->free_blocks_list;

        // The head of the list moves to the next free block.
        pool->free_blocks_list = *((uintptr_t *) pool->free_blocks_list);

        // The count of free blocks decreases by one.
        pool->free_blocks = pool->free_blocks - 1;

    }

    return block;

}

void termina__shared__pool__give(const termina__id_t pool_id,
                                 void * const block,
                                 termina__error_code_t * const status) {

    termina__shared__pool_t * pool = NULL;

    uintptr_t ptr = (uintptr_t)block;

    *status = termina__error__none;

    // The identifier of the pool is checked against the number of pools.
    if (termina__shared__pool__is_valid_id(pool_id)) {

        pool = &termina__shared__pool_object_table[pool_id];

    } else {

        *status = termina__error__invalid_id;

    }

    // The address must lie within the memory area and at the start of a
    // block.
    if ((NULL != pool) && (ptr >= pool->memory_area)
        && (ptr < (pool->memory_area + pool->memory_area_size))
        && (((ptr - pool->memory_area) % pool->block_size) == 0U)) {

        // The block holds the address of the current head of the list.

        *((uintptr_t *) ptr) = pool->free_blocks_list;

        // The block becomes the head of the list.
        pool->free_blocks_list = ptr;

        // The count of free blocks increases by one.
        pool->free_blocks = pool->free_blocks + 1;

    } else if (termina__error__none == *status) {

        *status = termina__error__invalid_block;

    }

}

size_t termina__shared__pool__in_use(const termina__id_t pool_id) {

    size_t in_use = 0U;

    const termina__shared__pool_t * pool = NULL;

    if (termina__shared__pool__is_valid_id(pool_id)) {

        pool = &termina__shared__pool_object_table[pool_id];

    }

    // A pool that was never initialized has a block size of zero.
    if ((NULL != pool) && (pool->block_size > 0U)) {

        // The pool holds memory_area_size / block_size blocks.
        in_use = (pool->memory_area_size / pool->block_size) - pool->free_blocks;

    }

    return in_use;

}

void termina__pool__alloc(const termina__event_t * const termina__ev,
                           void * const termina__this,
                           Option__box * const opt) {

    termina__pool_t * self = (termina__pool_t * const)termina__this;

    termina__error_code_t status = termina__error__none;

    termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    void * block = termina__shared__pool__take(self->pool_id, &status);

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type);

    // The exception is raised after the unlock, since the handler may use the
    // same pool.
    if (termina__error__none != status) {

        termina__except__runtime_failure((uintptr_t)__builtin_return_address(0),
                                         termina__runtime_operation__pool_alloc,
                                         status);

    }

    opt->_variant = Option__None;

    if (NULL != block) {

        opt->_variant = Option__Some;

        opt->Some._0.data = block;
        opt->Some._0.pool = (termina__pool_t *)self;

    }

}

void termina__pool__free(const termina__event_t * const termina__ev,
                          void * const termina__this,
                          termina__box_t element) {

    termina__pool_t * self = (termina__pool_t * const)termina__this;

    termina__error_code_t status = termina__error__none;

    // The list of free blocks is the one alloc takes blocks from, so it is
    // updated under the same lock.
    termina__resource__lock(&termina__ev->owner, &self->_lock_type);

    termina__shared__pool__give(self->pool_id, element.data, &status);

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type);

    // The exception is raised after the unlock, since the handler may use the
    // same pool.
    if (termina__error__none != status) {

        termina__except__runtime_failure((uintptr_t)__builtin_return_address(0),
                                         termina__runtime_operation__pool_free,
                                         status);

    }

}