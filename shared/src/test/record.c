#include <termina.h>
#include <termina/shared/test.h>

#include <stdatomic.h>
#include <string.h>

static termina__test__header_t * termina__shared__test__header = NULL;
static uint8_t * termina__shared__test__area = NULL;

void termina__test__init(void) {

    static const uint8_t magic[8] = { 'T', 'R', 'M', 'T', 'E', 'S', 'T', '\0' };

    termina__os__test__open(&termina__shared__test__header, &termina__shared__test__area);

    termina__test__header_t * const header = termina__shared__test__header;

    (void)memcpy(header->magic, magic, sizeof(magic));
    header->version = TERMINA__TEST__VERSION;
    header->flags = 0U;
    header->stamp = termina__test__stamp;
    header->capacity = termina__test__capacity;
    header->write_offset = 0U;
    header->cases_ended = 0U;
    header->checks_failed = 0U;
    header->checks_passed = 0U;
    header->last_step = 0U;
    header->anchor = (uintptr_t)&termina__test__stamp;

    return;

}

void termina__shared__test__write(const uint8_t * const record, const size_t size) {

    termina__test__header_t * const header = termina__shared__test__header;

    if (size > (size_t)(header->capacity - header->write_offset)) {

        header->flags = (uint16_t)(header->flags | TERMINA__TEST__FLAG_OVERFLOW);

    } else {

        (void)memcpy(&termina__shared__test__area[header->write_offset], record, size);

        // The record is complete before the offset that makes it visible
        atomic_signal_fence(memory_order_release);

        header->write_offset = header->write_offset + (uint32_t)size;

    }

    return;

}

_Noreturn void termina__test__end(void) {

    const uint8_t record[1] = { (uint8_t)termina__test__tag__end };

    termina__shared__test__write(record, sizeof(record));

    termina__os__test__halt();

}
