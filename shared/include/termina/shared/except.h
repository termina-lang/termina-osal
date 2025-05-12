#ifndef __TERMINA__SHARED__EXCEPT_H__
#define __TERMINA__SHARED__EXCEPT_H__

#include <termina.h>

typedef struct {

    void * handler_object;
    __termina_system_except_action_t handler_action;
    
} __termina_emitter_system_except_t;

extern __termina_emitter_system_except_t system_except;

/**
 * \brief Initializes the system exception emitter. This function is implemented
 *        for each operating system.
 */
void __termina_os_except__init_emitter(void * const handler_object,
                                        const __termina_system_except_action_t handler_action);


#endif // __TERMINA__SHARED__EXCEPT_H__

