/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Operations on the list of free blocks of a pool.
 */

#ifndef TERMINA__SHARED__POOL_H__
#define TERMINA__SHARED__POOL_H__

#include <termina.h>

/**
 * @brief Takes the first block of the list of free blocks of a pool.
 *
 * The caller must hold the lock of the pool.
 *
 * @param[in]  pool_id  Identifier of the pool.
 * @param[out] status   `termina__error__invalid_id` if the identifier is not
 *                      valid, or `termina__error__none` otherwise.
 *
 * @return The address of the block, or `NULL` if the identifier is not valid
 *         or the pool has no free blocks.
 */
void * termina__shared__pool__take(const termina__id_t pool_id,
                                   termina__error_code_t * const status);

/**
 * @brief Puts a block back at the head of the list of free blocks of a pool.
 *
 * The caller must hold the lock of the pool.
 *
 * @param[in]  pool_id  Identifier of the pool.
 * @param[in]  block    Address of the block.
 * @param[out] status   `termina__error__invalid_id` if the identifier is not
 *                      valid, `termina__error__invalid_block` if the address
 *                      is not the start of a block of the pool, or
 *                      `termina__error__none` otherwise.
 */
void termina__shared__pool__give(const termina__id_t pool_id,
                                 void * const block,
                                 termina__error_code_t * const status);

/**
 * @brief Gets the number of blocks of a pool that are allocated.
 *
 * The caller must hold the lock of the pool.
 *
 * @param[in] pool_id  Identifier of the pool.
 *
 * @return The number of blocks of the pool minus its free blocks, or zero if
 *         the identifier is not valid or the pool was never initialized.
 */
size_t termina__shared__pool__in_use(const termina__id_t pool_id);

#endif // TERMINA__SHARED__POOL_H__
