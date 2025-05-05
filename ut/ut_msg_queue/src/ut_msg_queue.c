
#include <termina.h>

void task1(void * const arg) {

    int32_t status = 0;

    TimeVal delay = {1, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

    uint32_t data = 0;

    char str[14];
    str[0] = 'T'; str[1] = 'a';
    str[2] = 's'; str[3] = 'k';
    str[4] = ' '; str[5] = '1';
    str[6] = ' '; str[7] = 's';
    str[8] = 't'; str[9] = 'a';
    str[10] = 'r'; str[11] = 't';
    str[12] = 'e'; str[13] = 'd';

    SystemEntry__println(14, str);

    for (;;) {
        __termina_msg_queue__send(0, &data, &status);
        __termina_msg_queue__recv(1, &data, &status);

        char str2[20];
        str2[0] = 'T'; str2[1] = 'a';
        str2[2] = 's'; str2[3] = 'k';
        str2[4] = ' '; str2[5] = '1';
        str2[6] = ' '; str2[7] = '-';
        str2[8] = ' '; str2[9] = 'r';
        str2[10] = 'e'; str2[11] = 'c';
        str2[12] = 'e'; str2[13] = 'i';
        str2[14] = 'v'; str2[15] = 'e';
        str2[16] = 'd'; str2[17] = ' ';
        str2[18] = ':'; str2[19] = ' ';

        SystemEntry__print(20, str2);

        SystemEntry__println_u32(data, decimal);
        
        SystemEntry__delay_in(&delay);
    }

    return;

}

void task2(void * const arg) {

    int32_t status = 0;

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

    uint32_t data = 0;

    char str[14];
    str[0] = 'T'; str[1] = 'a';
    str[2] = 's'; str[3] = 'k';
    str[4] = ' '; str[5] = '2';
    str[6] = ' '; str[7] = 's';
    str[8] = 't'; str[9] = 'a';
    str[10] = 'r'; str[11] = 't';
    str[12] = 'e'; str[13] = 'd';

    SystemEntry__println(14, str);

    for (;;) {
        __termina_msg_queue__recv(0, &data, &status);

        char str2[20];
        str2[0] = 'T'; str2[1] = 'a';
        str2[2] = 's'; str2[3] = 'k';
        str2[4] = ' '; str2[5] = '2';
        str2[6] = ' '; str2[7] = '-';
        str2[8] = ' '; str2[9] = 'r';
        str2[10] = 'e'; str2[11] = 'c';
        str2[12] = 'e'; str2[13] = 'i';
        str2[14] = 'v'; str2[15] = 'e';
        str2[16] = 'd'; str2[17] = ' ';
        str2[18] = ':'; str2[19] = ' ';

        SystemEntry__print(20, str2);

        SystemEntry__println_u32(data, decimal);

        data = data + 1;

        __termina_msg_queue__send(1, &data, &status);
    }

    return;

}


void __termina_app__init(int32_t * const status) {

    *status = 0;

    __termina_msg_queue__init(0, sizeof(uint32_t), 10, status);
    __termina_msg_queue__init(1, sizeof(uint32_t), 10, status);

    __termina_task__init(0, 10, 4096, task1, NULL, status);
    __termina_task__init(1, 8, 4096, task2, NULL, status);

    return;

}
