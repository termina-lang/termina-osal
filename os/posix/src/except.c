#include <termina.h>
#include <termina/shared/except.h>
#include <termina/os/posix/signal.h>

void termina__os__except__init_emitter(void) {
    
    // Nothing to do for POSIX
    return;
    
}

void termina__os__except__enter(void) {

    // The signals emulate the interrupts of the target, and an exception is
    // raised with whatever was being done left halfway.
    termina__posix__signal__disable();

}
