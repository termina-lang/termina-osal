#include <termina.h>
#include <termina/shared/except.h>

#include <FreeRTOS.h>

void termina__os__except__init_emitter(void) {
    
    // Nothing to do for FreeRTOS
    return;
    
}

void termina__os__except__enter(void) {

    // Not taskENTER_CRITICAL: it keeps a nesting count that this path would
    // never unwind, and it has a different macro for interrupt context, which
    // a function that serves both cannot use.
    portDISABLE_INTERRUPTS();

}
