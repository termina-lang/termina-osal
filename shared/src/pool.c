
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
    int32_t * const status) {

    termina__id_t pool_id = ((termina__pool_t * const)self)->pool_id;

    *status = 0;

    if (!termina__shared__pool__is_valid_id(pool_id)) {

        *status = -1;

    } else if (0 == block_size) {

        /* 
         * We are going to assume that block_size can never be zero.
         * If it were zero, then we must take action from the runtime
         * and, as default, go nuclear (rtems_shutdown_executive()).
         */

        *status = -1;

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

        /*
         * Adjust the size of the element so that it is a multiple of
         * TERMINA__POOL__MINIMUM_BLOCK_SIZE.
         */

        pool->block_size = block_size + 
            (TERMINA__POOL__MINIMUM_BLOCK_SIZE - 
                (block_size % TERMINA__POOL__MINIMUM_BLOCK_SIZE));

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
    // - Aligned to TERMINA_MINIMUM_BLOCK_SIZE
    if ((NULL != pool) && (ptr >= pool->memory_area)
        && ((ptr % TERMINA__POOL__MINIMUM_BLOCK_SIZE) == 0)
        && (ptr < (pool->memory_area + pool->memory_area_size))) {

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