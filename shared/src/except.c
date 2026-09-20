
#include <termina.h>
#include <termina/shared/except.h>

termina__emitter_system_except_t system_except;

void termina__except__init_emitter(void * const handler_object,
                                    const termina__system_except_action_t handler_action) {

    system_except.handler_object = handler_object;
    system_except.handler_action = handler_action;

    termina__os__except__init_emitter();

}
