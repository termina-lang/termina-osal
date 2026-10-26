#ifndef TERMINA__TEST__POOL_H__
#define TERMINA__TEST__POOL_H__

#include <termina/types.h>

/**
 * \brief Type of the TestPool objects.
 *
 * A pool of the OSAL with the counters that the cases read and set.
 */
typedef struct {

    termina__pool_t pool;

    //! Maximum number of blocks in use since the start of the case.
    size_t max_in_use;

    //! Number of calls to alloc that will still fail.
    size_t pending_fails;

} termina__test__pool_t;

/**
 * \brief Initializes a TestPool, with both counters at zero.
 *
 * The reset of a unit test calls it again before each case.
 *
 * @param[in]  self              the TestPool object.
 * @param[in]  p_memory_area     the memory area of the blocks.
 * @param[in]  memory_area_size  the size of the memory area in bytes.
 * @param[in]  block_size        the size of the type of the blocks.
 * @param[out] status            Zero if OK or another value in case of an error.
 */
void termina__test__pool__init(termina__test__pool_t * const self,
                               void * const p_memory_area,
                               const size_t memory_area_size,
                               const size_t block_size,
                               termina__error_code_t * const status);

/**
 * \brief Allocates a block, or yields None while there are failures to force.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestPool object.
 * @param[out] opt            the block allocated, or None.
 */
void termina__test__pool__alloc(const termina__event_t * const termina__ev,
                                void * const termina__this,
                                Option__box * const opt);

/**
 * \brief Returns a block to the pool.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestPool object.
 * @param[in]  element        the box of the block.
 */
void termina__test__pool__free(const termina__event_t * const termina__ev,
                               void * const termina__this,
                               termina__box_t element);

/**
 * \brief Gets the number of blocks in use.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestPool object.
 * @param[out] n              the number of blocks in use.
 */
void termina__test__pool__in_use(const termina__event_t * const termina__ev,
                                 const void * const termina__this,
                                 size_t * const n);

/**
 * \brief Gets the maximum number of blocks in use since the start of the case.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestPool object.
 * @param[out] n              the maximum number of blocks in use.
 */
void termina__test__pool__max_in_use(const termina__event_t * const termina__ev,
                                     const void * const termina__this,
                                     size_t * const n);

/**
 * \brief Makes the next n calls to alloc yield None.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the TestPool object.
 * @param[in]  n              the number of calls to alloc that will fail.
 */
void termina__test__pool__fail_allocs(const termina__event_t * const termina__ev,
                                      void * const termina__this,
                                      const size_t n);

#endif // TERMINA__TEST__POOL_H__
