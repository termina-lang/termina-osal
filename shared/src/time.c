
#include <termina.h>

#include <termina/shared/time.h>

void __termina_shared__add_timeval(TimeVal * const lhs, const TimeVal * const rhs) {

    lhs->tv_sec = lhs->tv_sec + rhs->tv_sec;
    lhs->tv_usec = lhs->tv_usec + rhs->tv_usec;

    if (lhs->tv_usec >= 1000000U) {

        lhs->tv_sec = lhs->tv_sec + lhs->tv_usec / 1000000U;
        lhs->tv_usec = lhs->tv_usec % 1000000U;

    }

}
