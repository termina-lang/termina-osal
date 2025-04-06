
#include <termina.h>

void task1(void * const arg) {

    Status status;
    status.__variant = Status__Success;

    TimeVal delay = {1, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

    uint32_t data = 0;

    char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE];
    str[0] = 'T'; str[1] = 'a';
    str[2] = 's'; str[3] = 'k';
    str[4] = ' '; str[5] = '1';
    str[6] = ' '; str[7] = 's';
    str[8] = 't'; str[9] = 'a';
    str[10] = 'r'; str[11] = 't';
    str[12] = 'e'; str[13] = 'd';
    for (size_t i = 14; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
        str[i] = '\0';
    }

    SystemEntry__println(str);

    for (;;) {
        __termina_msg_queue__send(0, &data, &status);
        __termina_msg_queue__recv(1, &data, &status);

        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '1';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'r';
        str[10] = 'e'; str[11] = 'c';
        str[12] = 'e'; str[13] = 'i';
        str[14] = 'v'; str[15] = 'e';
        str[16] = 'd'; str[17] = ' ';
        str[18] = ':'; str[19] = ' ';
        for (size_t i = 20; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }

        SystemEntry__print(str);

        SystemEntry__println_u32(data, decimal);
        
        SystemEntry__delay_in(&delay);
    }

    return;

}

void task2(void * const arg) {

    Status status;
    status.__variant = Status__Success;

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

    uint32_t data = 0;

    char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE];

    str[0] = 'T'; str[1] = 'a';
    str[2] = 's'; str[3] = 'k';
    str[4] = ' '; str[5] = '2';
    str[6] = ' '; str[7] = 's';
    str[8] = 't'; str[9] = 'a';
    str[10] = 'r'; str[11] = 't';
    str[12] = 'e'; str[13] = 'd';
    for (size_t i = 14; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
        str[i] = '\0';
    }

    SystemEntry__println(str);

    for (;;) {
        __termina_msg_queue__recv(0, &data, &status);

        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '2';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'r';
        str[10] = 'e'; str[11] = 'c';
        str[12] = 'e'; str[13] = 'i';
        str[14] = 'v'; str[15] = 'e';
        str[16] = 'd'; str[17] = ' ';
        str[18] = ':'; str[19] = ' ';
        for (size_t i = 20; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }

        SystemEntry__print(str);

        SystemEntry__println_u32(data, decimal);

        data = data + 1;

        __termina_msg_queue__send(1, &data, &status);
    }

    return;

}


void __termina_app__init(Status * const status) {

    status->__variant = Status__Success;

    __termina_msg_queue__init(0, sizeof(uint32_t), 10, status);
    __termina_msg_queue__init(1, sizeof(uint32_t), 10, status);

    __termina_task__init(0, 10, 4096, task1, NULL, status);
    __termina_task__init(1, 8, 4096, task2, NULL, status);

    return;

}
