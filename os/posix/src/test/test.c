/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Test operations of the POSIX emulation: record in a mapped file,
 *        timing verdict and halt.
 */

#include <termina.h>
#include <termina/shared/test.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void termina__os__test__open(termina__test__header_t ** const header,
                             uint8_t ** const area) {

    const char * const path = getenv("TERMINA_TEST_RECORD");

    if (NULL == path) {

        // With no record file, the record stays in memory.
        *header = &termina__test__header;
        *area = termina__test__area;

    } else {

        const size_t size = sizeof(termina__test__header_t) + (size_t)termina__test__capacity;
        void * mapping = MAP_FAILED;

        const int fd = open(path, O_RDWR);

        if (fd >= 0) {

            mapping = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            (void)close(fd);

        }

        if (MAP_FAILED == mapping) {

            perror("termina test record");
            exit(EXIT_FAILURE);

        }

        *header = (termina__test__header_t *)mapping;
        *area = (uint8_t *)mapping + sizeof(termina__test__header_t);

    }

    return;

}

_Bool termina__os__test__has_timing(void) {

    // POSIX is a deployment platform and is exempt from the timing requirements.
    return false;

}

_Noreturn void termina__os__test__halt(void) {

    exit(EXIT_SUCCESS);

}
