#include <termina.h>
#include <termina/shared/pool.h>

void termina__test__pool__init(termina__test__pool_t * const self,
                               void * const p_memory_area,
                               const size_t memory_area_size,
                               const size_t block_size,
                               termina__error_code_t * const status) {

    termina__pool__init(&self->pool, p_memory_area, memory_area_size, block_size, status);

    self->max_in_use = 0U;
    self->pending_fails = 0U;

    return;

}

void termina__test__pool__alloc(const termina__event_t * const termina__ev,
                                void * const termina__this,
                                Option__box * const opt) {

    termina__test__pool_t * self = (termina__test__pool_t * const)termina__this;

    termina__error_code_t status = termina__error__none;

    void * block = NULL;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->pool._lock_type);

    if (self->pending_fails > 0U) {

        // A forced failure takes no block
        self->pending_fails = self->pending_fails - 1U;

    } else {

        block = termina__shared__pool__take(self->pool.pool_id, &status);

        const size_t in_use = termina__shared__pool__in_use(self->pool.pool_id);

        if (in_use > self->max_in_use) {

            self->max_in_use = in_use;

        }

    }

    termina__resource__unlock(&termina__ev->owner, &self->pool._lock_type, termina__lock);

    // Raised after the unlock, since the handler may use the same pool
    if (termina__error__none != status) {

        termina__except__runtime_failure((uintptr_t)__builtin_return_address(0),
                                         termina__runtime_operation__pool_alloc,
                                         status);

    }

    opt->_variant = Option__None;

    if (NULL != block) {

        opt->_variant = Option__Some;

        opt->Some._0.data = block;
        opt->Some._0.pool = &self->pool;

    }

}

void termina__test__pool__free(const termina__event_t * const termina__ev,
                               void * const termina__this,
                               termina__box_t element) {

    termina__test__pool_t * self = (termina__test__pool_t * const)termina__this;

    termina__pool__free(termina__ev, &self->pool, element);

}

void termina__test__pool__in_use(const termina__event_t * const termina__ev,
                                 const void * const termina__this,
                                 size_t * const n) {

    const termina__test__pool_t * self = (const termina__test__pool_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->pool._lock_type);

    *n = termina__shared__pool__in_use(self->pool.pool_id);

    termina__resource__unlock(&termina__ev->owner, &self->pool._lock_type, termina__lock);

}

void termina__test__pool__max_in_use(const termina__event_t * const termina__ev,
                                     const void * const termina__this,
                                     size_t * const n) {

    const termina__test__pool_t * self = (const termina__test__pool_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->pool._lock_type);

    *n = self->max_in_use;

    termina__resource__unlock(&termina__ev->owner, &self->pool._lock_type, termina__lock);

}

void termina__test__pool__fail_allocs(const termina__event_t * const termina__ev,
                                      void * const termina__this,
                                      const size_t n) {

    termina__test__pool_t * self = (termina__test__pool_t * const)termina__this;

    termina__lock_t termina__lock = termina__resource__lock(
        &termina__ev->owner, &self->pool._lock_type);

    self->pending_fails = n;

    termina__resource__unlock(&termina__ev->owner, &self->pool._lock_type, termina__lock);

}
