#ifndef TERMINA__TEST__CHANNEL_H__
#define TERMINA__TEST__CHANNEL_H__

#include <termina/types.h>

/**
 * \brief Type of the access ports to a TestChannel.
 *
 * The same for every type of message. The object of a TestChannel is the
 * termina__msg_queue_t of the channel.
 */
typedef struct {

    void * _that;
    void (*pending) (const termina__event_t * const, const void * const, size_t * const);
    void (*take) (const termina__event_t * const, void * const,
                  termina__enum__Option_t * const, void * const);

} termina__test__channel_access_t;

/**
 * \brief Gets the number of messages in the channel.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the channel.
 * @param[out] n              the number of messages.
 */
void termina__test__channel__pending(const termina__event_t * const termina__ev,
                                     const void * const termina__this,
                                     size_t * const n);

/**
 * \brief Removes the oldest message of the channel, without blocking.
 *
 * @param[in]  termina__ev    the event that is being processed.
 * @param[in]  termina__this  the channel.
 * @param[out] variant        Option__Some if a message was taken, Option__None otherwise.
 * @param[out] element        the payload of the option, where the message is copied.
 */
void termina__test__channel__take(const termina__event_t * const termina__ev,
                                  void * const termina__this,
                                  termina__enum__Option_t * const variant,
                                  void * const element);

/**
 * \brief Removes every message of the channel and its events.
 *
 * The reset of a unit test calls it before each case.
 *
 * @param[in]  channel  the channel.
 */
void termina__test__channel__flush(const termina__msg_queue_t * const channel);

#endif // TERMINA__TEST__CHANNEL_H__
