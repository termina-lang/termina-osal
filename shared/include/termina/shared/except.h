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
void termina__os_except__init_emitter(void);


#endif // TERMINA__SHARED__EXCEPT_H__

