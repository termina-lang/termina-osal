
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>

#if defined(TERMINA__TEST__CLOCK)
#include <termina/shared/test.h>
#endif

void SystemEntry__clock_get_uptime(const termina__event_t * const termina__ev,
                                   const void * const termina__this,
                                   TimeVal * const uptime) {

    (void)termina__ev; // Unused parameter
    (void)termina__this; // Unused parameter

#if defined(TERMINA__TEST__CLOCK)
    termina__shared__test__clock_get(uptime);
#else
    termina__os__time__clock_get_uptime(uptime);
#endif

    return;

}

