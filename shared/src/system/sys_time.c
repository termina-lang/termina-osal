
#include <termina.h>

#include <termina/system/sys_time.h>
#include <termina/shared/time.h>

void SystemEntry__clock_get_uptime(const termina__event_t * const termina__ev,
                                   TimeVal * const uptime) {

    (void)termina__ev; // Unused parameter

    termina__os__time__clock_get_uptime(uptime);

    return;

}

