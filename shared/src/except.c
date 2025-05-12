
#include <termina.h>
#include <termina/shared/except.h>

__termina_emitter_system_except_t system_except;

void __termina_except__init_emitter(void * const handler_object,
                                    const __termina_system_except_action_t handler_action) {

    system_except.handler_object = handler_object;
    system_except.handler_action = handler_action;

    __termina_os_except__init_emitter();

}
