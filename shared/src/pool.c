
#include <termina.h>

#include <stdbool.h>

/**
 * \brief Structure used to implement memory pools.
 */
typedef struct {

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
 * \brief Size of the pool object table.
 */
#define TERMINA__SHARED__POOL_TABLE_SIZE TERMINA__APP_CONFIG__POOLS

/**
 * \brief Checks whether a pool identifier is valid.
 *
 * @param[in] pool_id the pool identifier.
 *
 * @return true if the identifier is less than the number of pools defined in
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

        // Init the pool as if we were memseting it with zeores

        for (size_t i = 0; i < sizeof(termina__shared__pool_t); i = i + 1) {

            *(((uint8_t *) pool) + i) = 0;

        }

        // set the pool attributes.

        pool->pool_id = pool_id;

        pool->memory_area = (uintptr_t)p_memory_area;

        pool->memory_area_size = memory_area_size;

        // A block size that is a multiple of the alignment keeps every block
        // aligned, since the memory area is.
        pool->block_size = termina__pool__block_size(block_size);

        // Init the list of free blocks to the start of the memory area
        pool->free_blocks_list = pool->memory_area;

        // Obtain the maximum number of free blocks.
        pool->free_blocks = pool->memory_area_size / pool->block_size;

        uintptr_t ptr = pool->free_blocks_list;

        // Iterate for the number of blocks.
        for (size_t i = 0; i < (pool->free_blocks - 1); i = i + 1) {

            // Write pointer to the next block
            *(uintptr_t *)ptr = ptr + pool->block_size;

            // Go the next block
            ptr = ptr + pool->block_size;

        }

        // NULL the "next" pointer of the last block.
        *((uintptr_t *) ptr) = (uintptr_t)NULL;

    }

    return;

}

void termina__pool__alloc(const termina__event_t * const termina__ev,
                           void * const termina__this,
                           Option__box * const opt) {

    termina__pool_t * self = (termina__pool_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->_lock_type);

    termina__shared__pool_t * pool = NULL;

    opt->Some._0.data = NULL;

    if (termina__shared__pool__is_valid_id(self->pool_id)) {
        
        pool = &termina__shared__pool_object_table[self->pool_id];

    }

    // Check the pool is not NULL and if there are free blocks and 
    if ((NULL != pool) && (pool->free_blocks > 0)) {

        // Get the pointer to the first free block in the list.
        opt->_variant = Option__Some;

        opt->Some._0.data = (void *)pool->free_blocks_list;
        opt->Some._0.pool = (termina__pool_t *)self;

        // Update the head of the free blocks list.
        pool->free_blocks_list = *((uintptr_t *) pool->free_blocks_list);

        // Decrease the number of free blocks.
        pool->free_blocks = pool->free_blocks - 1;

    }

    termina__resource__unlock(&termina__ev->owner, &self->_lock_type, termina__lock);

}

void termina__pool__free(const termina__event_t * const termina__ev,
                          void * const termina__this,
                          termina__box_t element) {

    (void)termina__ev;

    termina__pool_t * self = (termina__pool_t * const)termina__this;

    termina__shared__pool_t * pool = NULL;

    uintptr_t ptr = (uintptr_t)element.data;

    // Check if the pool's identifier is within the limits
    if (termina__shared__pool__is_valid_id(self->pool_id)) {
        
        pool = &termina__shared__pool_object_table[self->pool_id];

    }

    // Sanity check of the element's address
    // - Within the limits of the memory area
    // - At the start of a block
    if ((NULL != pool) && (ptr >= pool->memory_area)
        && (ptr < (pool->memory_area + pool->memory_area_size))
        && (((ptr - pool->memory_area) % pool->block_size) == 0U)) {

        // Add the block to the free blocks list.

        *((uintptr_t *) ptr) = pool->free_blocks_list;

        // Update the head of the free block list.
        pool->free_blocks_list = ptr;

        // Increase the number of free blocks.
        pool->free_blocks = pool->free_blocks + 1;

    } else {

        /* 
         * We are assuming that the address is always correct.
         * If it were not, then we must take action from the runtime
         * and, most likely, go nuclear (rtems_shutdown_executive()).
         */

    }

}