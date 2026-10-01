#ifndef TERMINA__SHARED__EXCEPT_H__
#define TERMINA__SHARED__EXCEPT_H__

#include <termina.h>

typedef struct {

    void * handler_object;
    termina__system_except_action_t handler_action;
    
} termina__emitter_system_except_t;

extern termina__emitter_system_except_t system_except;

/**
 * \brief Initializes the system exception emitter. This function is implemented
 *        for each operating system.
 */
void termina__os__except__init_emitter(void);

/**
 * \brief Stops whatever the operating system could run while an exception is
 *        being raised. Implemented for each operating system, and a no-op
 *        where there is nothing to stop.
 */
void termina__os__except__enter(void);

/**
 * \brief Raises the exception EActionFailure for the action of a handler that
 *        returned a failure.
 *
 * A handler has a single sink port, so the port is always 0.
 *
 * @param[in] handler_id  identifier of the handler.
 * @param[in] error_code  the value of the failure.
 */
_Noreturn void termina__shared__except__handler_failure(const termina__id_t handler_id,
                                              const int32_t error_code);


#endif // TERMINA__SHARED__EXCEPT_H__

