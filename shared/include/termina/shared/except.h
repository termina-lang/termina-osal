/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief System exception emitter and its initialization by the back-end.
 */

#ifndef TERMINA__SHARED__EXCEPT_H__
#define TERMINA__SHARED__EXCEPT_H__

#include <termina.h>

/**
 * @brief Type of the system exception emitter.
 */
typedef struct {

    //! Identifier of the emitter.
    termina__id_t emitter_id;
    //! Connection to the handler.
    termina__system_except_connection_t connection;

} termina__emitter_system_except_t;

/** @brief System exception emitter. */
extern termina__emitter_system_except_t system_except;

/**
 * @brief Initializes the system exception emitter.
 *
 * Each operating system implements this function.
 */
void termina__os__except__init_emitter(void);


#endif // TERMINA__SHARED__EXCEPT_H__

