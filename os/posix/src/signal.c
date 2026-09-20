
#include <termina.h>

#include <termina/os/posix/time.h>
#include <termina/os/posix/signal.h>
#include <termina/os/posix/keyboard.h>

#include <signal.h>


sigset_t signal_set;

uint32_t termina__posix__blocking_nesting_level;

void termina__posix__signal__init(void) {

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
    sa.sa_handler = termina__posix__time__tick_handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    // Install the signal handler for SIGUSR2
    struct sigaction sa_kbd;
    sa_kbd.sa_flags = 0;
    sa_kbd.sa_handler = termina__posix__keyboard__irq_handler;
    sigfillset(&sa_kbd.sa_mask);
    sigaction(SIGUSR2, &sa_kbd, NULL);

    termina__posix__blocking_nesting_level = 1;

    return;

}

void termina__posix__signal__disable(void) {


    if (0 == termina__posix__blocking_nesting_level) {

        // Block all signals
        pthread_sigmask(SIG_BLOCK, &signal_set, NULL);

    }

    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level + 1;

    return;

}

void termina__posix__signal__enable(void) {

    termina__posix__blocking_nesting_level = termina__posix__blocking_nesting_level - 1;

    if (0 == termina__posix__blocking_nesting_level) {

        // Unblock all signals
        pthread_sigmask(SIG_UNBLOCK, &signal_set, NULL);

    }

    return;

}