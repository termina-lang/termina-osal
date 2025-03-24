
#include <termina.h>

#include <termina/os/posix/time.h>
#include <termina/os/posix/signal.h>

#include <signal.h>


sigset_t signal_set;

uint32_t __posix_blocking_nesting_level;

void __posix_signal__init(void) {

    // Initialize signal masks
    sigfillset(&signal_set); 

    // We are blocking all signals except SIGINT
    // This makes SIGINT the only signal that is always unblocked
    sigdelset(&signal_set, SIGINT);

    // Set the signal mask
    // This mask will be inherited by all threads created by the main thread
    pthread_sigmask(SIG_SETMASK, &signal_set, NULL);

    // Install the signal handler for SIGALRM
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = __posix_time__tick_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    __posix_blocking_nesting_level = 1;

    return;

}

void __posix_signal__disable(void) {


    if (0 == __posix_blocking_nesting_level) {

        // Block all signals
        pthread_sigmask(SIG_BLOCK, &signal_set, NULL);

    }

    __posix_blocking_nesting_level = __posix_blocking_nesting_level + 1;

    return;

}

void __posix_signal__enable(void) {

    __posix_blocking_nesting_level = __posix_blocking_nesting_level - 1;

    if (0 == __posix_blocking_nesting_level) {

        // Unblock all signals
        pthread_sigmask(SIG_UNBLOCK, &signal_set, NULL);

    }

    return;

}