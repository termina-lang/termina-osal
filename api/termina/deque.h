#ifndef TERMINA__DEQUE_H__
#define TERMINA__DEQUE_H__

#include <termina/types.h>

/**
 * \brief Deque: a queue of boxes that only one task, handler or resource uses,
 *        into which boxes can be put at both ends and taken from the front.
 *
 * The boxes are kept in a ring over an array that the application declares.
 * Only the element connected to the deque accesses it, so it has no lock.
 */
typedef struct {

    //! Array that holds the boxes.
    termina__box_t * items;

    //! Number of boxes the deque can hold.
    size_t capacity;

    //! Position of the box at the front.
    size_t head;

    //! Number of boxes the deque holds.
    size_t count;

} termina__deque_t;

/**
 * \brief Initializes an empty deque.
 *
 * @param[out] self      pointer to the deque.
 * @param[in]  items     array that holds the boxes.
 * @param[in]  capacity  number of elements of the array.
 */
void termina__deque__init(termina__deque_t * const self,
                          termina__box_t * const items,
                          const size_t capacity);

/**
 * \brief Takes the box at the front of a deque.
 *
 * @param[in,out] self  pointer to the deque.
 * @param[out]    opt   the box, or None if the deque is empty.
 */
void termina__deque__take(termina__deque_t * const self,
                          Option__box * const opt);

/**
 * \brief Puts a box at the back of a deque.
 *
 * The transpiler only accepts a put into a deque that it proves has room. If
 * the deque is full anyway, the function raises ERuntimeFailure and leaves the
 * deque as it was.
 *
 * @param[in,out] self     pointer to the deque.
 * @param[in]     element  box to put into the deque.
 */
void termina__deque__put(termina__deque_t * const self,
                         const termina__box_t element);

/**
 * \brief Puts a box at the front of a deque, with the same check as
 * termina__deque__put.
 *
 * @param[in,out] self     pointer to the deque.
 * @param[in]     element  box to put into the deque.
 */
void termina__deque__put_front(termina__deque_t * const self,
                               const termina__box_t element);

/**
 * \brief Puts a box at the back of a deque if it has room.
 *
 * @param[in,out] self      pointer to the deque.
 * @param[in]     element   box to put into the deque.
 * @param[out]    rejected  the box if the deque is full, or None.
 */
void termina__deque__try_put(termina__deque_t * const self,
                             const termina__box_t element,
                             Option__box * const rejected);

/**
 * \brief Puts a box at the back of a deque, taking out the one at the front if
 * the deque is full.
 *
 * @param[in,out] self     pointer to the deque.
 * @param[in]     element  box to put into the deque.
 * @param[out]    evicted  the box taken out if the deque was full, or None.
 */
void termina__deque__replace(termina__deque_t * const self,
                             const termina__box_t element,
                             Option__box * const evicted);

#endif // TERMINA__DEQUE_H__
