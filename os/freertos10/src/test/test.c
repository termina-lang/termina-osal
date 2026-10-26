#include <termina.h>
#include <termina/shared/exec.h>
#include <termina/shared/test.h>

void termina__os__test__open(termina__test__header_t ** const header,
                             uint8_t ** const area) {

    *header = &termina__test__header;
    *area = termina__test__area;

    return;

}

_Bool termina__os__test__has_timing(void) {

    return true;

}

_Noreturn void termina__os__test__halt(void) {

    // With the interrupts disabled nothing else of the test runs
    termina__os__exec__quiesce();

    for (;;) {
    }

}
