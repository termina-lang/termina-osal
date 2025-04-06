
#include <termina.h>

/**
 * \brief Structure used to implement memory pools.
 */
typedef struct {

    __termina_id_t pool_id;

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

    //! The mutex that protects the pool (if required).
    __termina_id_t mutex_id;

} __termina_shared_pool_t;

static __termina_shared_pool_t __app_pool_object_table[__TERMINA_APP_CONFIG_POOLS];

void __termina_pool__init(void * const self,
    void * const p_memory_area, 
    size_t memory_area_size, 
    size_t block_size, 
    Status * const status) {

    __termina_id_t pool_id = ((__termina_pool_t * const)self)->pool_id;

    __termina_shared_pool_t * pool = NULL;
    status->__variant = Status__Success;

    if (pool_id >= __TERMINA_APP_CONFIG_POOLS) {

        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;

    }

    if (status->__variant == Status__Success) {

        pool = &__app_pool_object_table[pool_id];

        // Init the pool as if we were memseting it with zeores

        for (size_t i = 0; i < sizeof(__termina_shared_pool_t); i = i + 1) {

            *(((uint8_t *) pool) + i) = 0;

        }

        // set the pool attributes.

        pool->pool_id = pool_id;

        pool->memory_area = (uintptr_t)p_memory_area;

        pool->memory_area_size = memory_area_size;

        /*
         * Adjust the size of the element so that it is a multiple of
         * __TERMINA_POOL_MINIMUM_BLOCK_SIZE.
         */

        if (block_size > 0) { 

            pool->block_size = block_size + 
                (__TERMINA_POOL_MINIMUM_BLOCK_SIZE - 
                    (block_size % __TERMINA_POOL_MINIMUM_BLOCK_SIZE));

        } else {

            /* 
             * We are going to assume that block_size can never be zero.
             * If it were zero, then we must take action from the runtime
             * and, as default, go nuclear (rtems_shutdown_executive()).
             */

            status->__variant = Status__Error;
            status->Error.__0.__variant = Exception__InternalError;

        }

    }

    if (status->__variant == Status__Success) {

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

void __termina_pool__alloc(void * const self,
                           __option_box_t * const opt) {

    __termina_id_t pool_id = ((__termina_pool_t * const)self)->pool_id;

    __termina_shared_pool_t * pool = NULL;

    opt->Some.__0.data = NULL;

    if (pool_id <__TERMINA_APP_CONFIG_POOLS) {
        
        pool = &__app_pool_object_table[pool_id];

    }

    // Check the pool is not NULL and if there are free blocks and 
    if ((NULL != pool) && (pool->free_blocks > 0)) {

        // Get the pointer to the first free block in the list.
        opt->__variant = Some;

        opt->Some.__0.data = (void *)pool->free_blocks_list;
        opt->Some.__0.pool = (__termina_pool_t *)self;

        // Update the head of the free blocks list.
        pool->free_blocks_list = *((uintptr_t *) pool->free_blocks_list);

        // Decrease the number of free blocks.
        pool->free_blocks = pool->free_blocks - 1;

    }

}

void __termina_pool__alloc__mutex_lock(void * const self,
                                       __option_box_t * const opt) {
    
    Status status;
    status.__variant = Status__Success;

    __termina_id_t pool_id = ((__termina_pool_t * const)self)->pool_id;

    __termina_shared_pool_t * pool = NULL;

    if (pool_id <__TERMINA_APP_CONFIG_POOLS) {
        
        pool = &__app_pool_object_table[pool_id];

    }
    
    if (pool != NULL) {

        __termina_mutex__lock(pool->mutex_id, &status);
        __termina_pool__alloc(self, opt);
        __termina_mutex__unlock(pool->mutex_id, &status);

    }

}

void __termina_pool__alloc__task_lock(void * const self,
                                       __option_box_t * const opt) {

    __termina_task_lock_t lock = __termina_task__lock();
    __termina_pool__alloc(self, opt);
    __termina_task__unlock(lock);
    
}

void __termina_pool__alloc__event_lock(void * const self,
                                       __option_box_t * const opt) {

    __termina_event_lock_t lock = __termina_event__lock();
    __termina_pool__alloc(self, opt);
    __termina_event__unlock(lock);

}

void __termina_pool__free(void * const self,
                          __termina_box_t element) {

    __termina_id_t pool_id = ((__termina_pool_t * const)self)->pool_id;

    __termina_shared_pool_t * pool = NULL;

    uintptr_t ptr = (uintptr_t)element.data;

    // Check if the pool's identifier is within the limits
    if (pool_id <__TERMINA_APP_CONFIG_POOLS) {
        
        pool = &__app_pool_object_table[pool_id];

    }

    // Sanity check of the element's address
    // - Within the limits of the memory area
    // - Aligned to TERMINA_MINIMUM_BLOCK_SIZE
    if ((NULL != pool) && (ptr >= pool->memory_area)
        && ((ptr % __TERMINA_POOL_MINIMUM_BLOCK_SIZE) == 0)
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

void __termina_pool__free__mutex_lock(void * const self,
                                      __termina_box_t element) {
    
    Status status;
    status.__variant = Status__Success;

    __termina_id_t pool_id = ((__termina_pool_t * const)self)->pool_id;

    __termina_shared_pool_t * pool = NULL;

    if (pool_id <__TERMINA_APP_CONFIG_POOLS) {
        
        pool = &__app_pool_object_table[pool_id];

    }
    
    if (pool != NULL) {

        __termina_mutex__lock(pool->mutex_id, &status);
        __termina_pool__free(self, element);
        __termina_mutex__unlock(pool->mutex_id, &status);

    }

}


void __termina_pool__free__task_lock(void * const self,
                                     __termina_box_t element) {

    __termina_task_lock_t lock = __termina_task__lock();
    __termina_pool__free(self, element);
    __termina_task__unlock(lock);
    
}

void __termina_pool__free__event_lock(void * const self,
                                     __termina_box_t element) {

    __termina_event_lock_t lock = __termina_event__lock();
    __termina_pool__free(self, element);
    __termina_event__unlock(lock);

}
