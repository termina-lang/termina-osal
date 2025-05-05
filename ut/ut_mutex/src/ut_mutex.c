
#include <termina.h>

void task1(void * const arg) {

    int32_t status = 0;

    __termina_id_t port_id = 0;
    TimeVal timeval = {0, 0};
    TimeVal delay = {0, 200000U};
    TimeVal current = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

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

        __termina_msg_queue__recv(0, &port_id, &status);
        __termina_msg_queue__recv(1, &timeval, &status);

        char str2[25];
        str2[0] = 'T'; str2[1] = 'a';
        str2[2] = 's'; str2[3] = 'k';
        str2[4] = ' '; str2[5] = '1';
        str2[6] = ' '; str2[7] = 'r';
        str2[8] = 'e'; str2[9] = 'c';
        str2[10] = 'e'; str2[11] = 'i';
        str2[12] = 'v'; str2[13] = 'e';
        str2[14] = 'd'; str2[15] = ' ';
        str2[16] = 'p'; str2[17] = 'o';
        str2[18] = 'r'; str2[19] = 't';
        str2[20] = '_'; str2[21] = 'i';
        str2[22] = 'd'; str2[23] = ':';
        str2[24] = ' ';

        SystemEntry__print(25, str2);
        SystemEntry__print_char(' ');
        SystemEntry__println_usize(port_id, decimal);

        char str3[24];
        str3[0] = 'T'; str3[1] = 'a';
        str3[2] = 's'; str3[3] = 'k';
        str3[4] = ' '; str3[5] = '1';
        str3[6] = ' '; str3[7] = '-';
        str3[8] = ' '; str3[9] = 'R';
        str3[10] = 'e'; str3[11] = 'c';
        str3[12] = 'e'; str3[13] = 'i';
        str3[14] = 'v'; str3[15] = 'e';
        str3[16] = 'd'; str3[17] = ' ';
        str3[18] = 't'; str3[19] = 'i';
        str3[20] = 'm'; str3[21] = 'e';
        str3[22] = ':';
        str3[23] = ' ';

        SystemEntry__print(24, str3);
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(timeval.tv_sec, decimal);
        SystemEntry__print_char(' ');

        char str4[9];
        str4[0] = 's'; str4[1] = 'e';
        str4[2] = 'c'; str4[3] = 's';
        str4[4] = ' '; str4[5] = 'a';
        str4[6] = 'n'; str4[7] = 'd';
        str4[8] = ' ';

        SystemEntry__print(9, str4);

        SystemEntry__print_u32(timeval.tv_usec, decimal);
        SystemEntry__print_char(' ');

        char str5[5];
        str5[0] = 'u'; str5[1] = 's';
        str5[2] = 'e'; str5[3] = 'c';
        str5[4] = 's';

        SystemEntry__println(5, str5);

        __termina_mutex__lock(0, &status);

        SystemEntry__clock_get_uptime(&current);

        SystemEntry__print_char('(');
        SystemEntry__print_u32(current.tv_sec, decimal);
        SystemEntry__print_char(' ');
        SystemEntry__print_char(',');
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(current.tv_usec, decimal);
        SystemEntry__print_char(')');
        SystemEntry__print_char(' ');
        
        char str6[21];
        str6[0] = 'T'; str6[1] = 'a';
        str6[2] = 's'; str6[3] = 'k';
        str6[4] = ' '; str6[5] = '1';
        str6[6] = ' '; str6[7] = '-';
        str6[8] = ' '; str6[9] = 'l';
        str6[10] = 'o'; str6[11] = 'c';
        str6[12] = 'k'; str6[13] = 'e';
        str6[14] = 'd'; str6[15] = ' ';
        str6[16] = 'm'; str6[17] = 'u';
        str6[18] = 't'; str6[19] = 'e';
        str6[20] = 'x';

        SystemEntry__println(21, str6);

        SystemEntry__delay_in(&delay);

        SystemEntry__clock_get_uptime(&current);
        SystemEntry__print_char('(');
        SystemEntry__print_u32(current.tv_sec, decimal);
        SystemEntry__print_char(' ');
        SystemEntry__print_char(',');
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(current.tv_usec, decimal);
        SystemEntry__print_char(')');
        SystemEntry__print_char(' ');

        char str7[23];
        str7[0] = 'T'; str7[1] = 'a';
        str7[2] = 's'; str7[3] = 'k';
        str7[4] = ' '; str7[5] = '1';
        str7[6] = ' '; str7[7] = '-';
        str7[8] = ' '; str7[9] = 'r';
        str7[10] = 'e'; str7[11] = 'l';
        str7[12] = 'e'; str7[13] = 'a';
        str7[14] = 's'; str7[15] = 'e';
        str7[16] = 'd'; str7[17] = ' ';
        str7[18] = 'm'; str7[19] = 'u';
        str7[20] = 't'; str7[21] = 'e';
        str7[22] = 'x';

        SystemEntry__println(23, str7);

        __termina_mutex__unlock(0, &status);

    }

    return;

}

void task2(void * const arg) {

    int32_t status = 0;

    TimeVal delay = {0, 500000U};
    TimeVal current = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

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

        __termina_mutex__lock(0, &status);
        SystemEntry__clock_get_uptime(&current);

        SystemEntry__print_char('(');
        SystemEntry__print_u32(current.tv_sec, decimal);
        SystemEntry__print_char(' ');
        SystemEntry__print_char(',');
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(current.tv_usec, decimal);
        SystemEntry__print_char(')');
        SystemEntry__print_char(' ');
        
        char str2[21];
        str2[0] = 'T'; str2[1] = 'a';
        str2[2] = 's'; str2[3] = 'k';
        str2[4] = ' '; str2[5] = '2';
        str2[6] = ' '; str2[7] = '-';
        str2[8] = ' '; str2[9] = 'l';
        str2[10] = 'o'; str2[11] = 'c';
        str2[12] = 'k'; str2[13] = 'e';
        str2[14] = 'd'; str2[15] = ' ';
        str2[16] = 'm'; str2[17] = 'u';
        str2[18] = 't'; str2[19] = 'e';
        str2[20] = 'x';

        SystemEntry__println(21, str2);

        SystemEntry__delay_in(&delay);

        SystemEntry__clock_get_uptime(&current);

        SystemEntry__clock_get_uptime(&current);
        SystemEntry__print_char('(');
        SystemEntry__print_u32(current.tv_sec, decimal);
        SystemEntry__print_char(' ');
        SystemEntry__print_char(',');
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(current.tv_usec, decimal);
        SystemEntry__print_char(')');
        SystemEntry__print_char(' ');

        char str3[23];
        str3[0] = 'T'; str3[1] = 'a';
        str3[2] = 's'; str3[3] = 'k';
        str3[4] = ' '; str3[5] = '2';
        str3[6] = ' '; str3[7] = '-';
        str3[8] = ' '; str3[9] = 'r';
        str3[10] = 'e'; str3[11] = 'l';
        str3[12] = 'e'; str3[13] = 'a';
        str3[14] = 's'; str3[15] = 'e';
        str3[16] = 'd'; str3[17] = ' ';
        str3[18] = 'm'; str3[19] = 'u';
        str3[20] = 't'; str3[21] = 'e';
        str3[22] = 'x';

        SystemEntry__println(23, str3);

        __termina_mutex__unlock(0, &status);
    }

}

void __termina_app__init(int32_t * const status) {

    *status = 0;

    __termina_mutex__init(0, sizeof(__termina_id_t), 8, status);

    __termina_msg_queue__init(0, sizeof(__termina_id_t), 10, status);
    __termina_msg_queue__init(1, sizeof(TimeVal), 10, status);

    __termina_periodic_timer_connection_t connection;
    connection.type = __TerminaEmitterConnectionType__Task;
    connection.task.task_msg_queue_id = 0;
    connection.task.sink_msgq_id = 1;
    connection.task.sink_port_id = 0;

    TimeVal period = {1, 0};

    __termina_periodic_timer__init(0, &connection, &period, status);

    __termina_task__init(0, 8, 4096, task1, NULL, status);
    __termina_task__init(1, 10, 4096, task2, NULL, status);

    return;

}
