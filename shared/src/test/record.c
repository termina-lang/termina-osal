#include <termina.h>
#include <termina/shared/test.h>

#include <stdatomic.h>
#include <string.h>

static termina__test__header_t * termina__shared__test__header = NULL;
static uint8_t * termina__shared__test__area = NULL;
static size_t termina__shared__test__case_checks = 0U;

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

void termina__shared__test__pass(void) {

    termina__test__header_t * const header = termina__shared__test__header;

    header->checks_passed = header->checks_passed + 1U;
    termina__shared__test__case_checks = termina__shared__test__case_checks + 1U;

    return;

}

void termina__shared__test__fail(const termina__test__tag_t tag,
                                 const void * const where,
                                 const void * const actual,
                                 const void * const expected,
                                 const size_t size) {

    termina__test__header_t * const header = termina__shared__test__header;

    uint8_t record[1U + sizeof(size_t) + sizeof(void *) + (2U * sizeof(TimeVal))];
    size_t offset = 0U;

    header->checks_failed = header->checks_failed + 1U;
    termina__shared__test__case_checks = termina__shared__test__case_checks + 1U;

    record[0] = (uint8_t)tag;
    offset = 1U;

    (void)memcpy(&record[offset], &header->last_step, sizeof(size_t));
    offset = offset + sizeof(size_t);

    (void)memcpy(&record[offset], &where, sizeof(void *));
    offset = offset + sizeof(void *);

    if (size > 0U) {

        (void)memcpy(&record[offset], actual, size);
        offset = offset + size;

        (void)memcpy(&record[offset], expected, size);
        offset = offset + size;

    }

    termina__shared__test__write(record, offset);

    return;

}

void termina__shared__test__step(const size_t n) {

    termina__shared__test__header->last_step = n;

    return;

}

_Bool termina__test__selected(const uint16_t test_case) {

    const uint32_t selected = termina__shared__test__header->selected_case;

    return (0U == selected) || ((uint32_t)test_case == selected);

}

void termina__test__case_begin(const uint16_t test_case) {

    uint8_t record[1U + sizeof(uint16_t)];

    termina__shared__test__header->last_step = 0U;
    termina__shared__test__case_checks = 0U;

    record[0] = (uint8_t)termina__test__tag__case_begin;
    (void)memcpy(&record[1], &test_case, sizeof(uint16_t));

    termina__shared__test__write(record, sizeof(record));

    return;

}

void termina__test__case_end(void) {

    termina__test__header_t * const header = termina__shared__test__header;

    uint8_t record[1U + sizeof(size_t)];

    header->cases_ended = header->cases_ended + 1U;

    record[0] = (uint8_t)termina__test__tag__case_end;
    (void)memcpy(&record[1], &termina__shared__test__case_checks, sizeof(size_t));

    termina__shared__test__write(record, sizeof(record));

    return;

}

_Noreturn void termina__test__end(void) {

    const uint8_t record[1] = { (uint8_t)termina__test__tag__end };

    termina__shared__test__write(record, sizeof(record));

    termina__os__test__halt();

}
