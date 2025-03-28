
#include <termina.h>

static uint8_t __pool_pool_memory[__termina_pool__size(sizeof(uint32_t), 10U)];

void __termina_app__init(Status * const status) {

    status->__variant = Status__Success;

    __option_box_t opt;

    __termina_pool__init(0, __pool_pool_memory,
                         sizeof(__pool_pool_memory), sizeof(uint32_t), 
                         __TERMINA_ID_INVALID, status);

    __termina_pool__alloc(0, &opt);

    if (opt.__variant == Some) {

        __termina_box_t box = opt.Some.__0;
        *(uint32_t *)box.data = 0x12345678;

        __termina_pool__free(0, box);
        
    } else {
        status->__variant = Status__Error;
        status->Error.__0.__variant = Exception__InternalError;
    }

    return;

}
