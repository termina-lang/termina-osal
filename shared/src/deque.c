#include <termina.h>

void termina__deque__init(termina__deque_t * const self,
                          termina__box_t * const items,
                          const size_t capacity) {

    self->items = items;
    self->capacity = capacity;
    self->head = 0U;
    self->count = 0U;

}

void termina__deque__take(termina__deque_t * const self,
                          Option__box * const opt) {

    if (0U == self->count) {

        opt->_variant = Option__None;

    } else {

        opt->_variant = Option__Some;
        opt->Some._0 = self->items[self->head];

        self->head = (self->head + 1U) % self->capacity;
        self->count = self->count - 1U;

    }

}

void termina__deque__put(termina__deque_t * const self,
                         const termina__box_t element) {

    if (self->count < self->capacity) {

        self->items[(self->head + self->count) % self->capacity] = element;
        self->count = self->count + 1U;

    } else {

        termina__except__runtime_failure(termina__runtime_operation__deque_put,
                                         termina__error__deque_full);

    }

}

void termina__deque__put_front(termina__deque_t * const self,
                               const termina__box_t element) {

    if (self->count < self->capacity) {

        self->head = (self->head + self->capacity - 1U) % self->capacity;
        self->items[self->head] = element;
        self->count = self->count + 1U;

    } else {

        termina__except__runtime_failure(termina__runtime_operation__deque_put,
                                         termina__error__deque_full);

    }

}

void termina__deque__try_put(termina__deque_t * const self,
                             const termina__box_t element,
                             Option__box * const rejected) {

    if (self->count < self->capacity) {

        self->items[(self->head + self->count) % self->capacity] = element;
        self->count = self->count + 1U;

        rejected->_variant = Option__None;

    } else {

        rejected->_variant = Option__Some;
        rejected->Some._0 = element;

    }

}

void termina__deque__replace(termina__deque_t * const self,
                             const termina__box_t element,
                             Option__box * const evicted) {

    if (self->count < self->capacity) {

        self->items[(self->head + self->count) % self->capacity] = element;
        self->count = self->count + 1U;

        evicted->_variant = Option__None;

    } else {

        // The deque is full, so the back is where the front was
        evicted->_variant = Option__Some;
        evicted->Some._0 = self->items[self->head];

        self->items[self->head] = element;
        self->head = (self->head + 1U) % self->capacity;

    }

}
