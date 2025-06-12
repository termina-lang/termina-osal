
#include <termina.h>

void the_task(void * const arg) {

    __termina_event_t event;

    int32_t status = 0;

    TimeVal timeval = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;


    for (;;) {
        __termina_msg_queue__recv(0, &event, &status);
        __termina_msg_queue__recv(1, &timeval, &status);

        char str[25];
        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '1';
        str[6] = ' '; str[7] = 'r';
        str[8] = 'e'; str[9] = 'c';
        str[10] = 'e'; str[11] = 'i';
        str[12] = 'v'; str[13] = 'e';
        str[14] = 'd'; str[15] = ' ';
        str[16] = 'p'; str[17] = 'o';
        str[18] = 'r'; str[19] = 't';
        str[20] = '_'; str[21] = 'i';
        str[22] = 'd'; str[23] = ':';
        str[24] = ' ';

        SystemEntry__print(&event, 25, str);
        SystemEntry__print_char(&event, ' ');
        SystemEntry__println_usize(&event, event.port_id, decimal);

        char str2[24];
        str2[0] = 'T'; str2[1] = 'a';
        str2[2] = 's'; str2[3] = 'k';
        str2[4] = ' '; str2[5] = '1';
        str2[6] = ' '; str2[7] = '-';
        str2[8] = ' '; str2[9] = 'R';
        str2[10] = 'e'; str2[11] = 'c';
        str2[12] = 'e'; str2[13] = 'i';
        str2[14] = 'v'; str2[15] = 'e';
        str2[16] = 'd'; str2[17] = ' ';
        str2[18] = 't'; str2[19] = 'i';
        str2[20] = 'm'; str2[21] = 'e';
        str2[22] = ':';
        str2[23] = ' ';

        SystemEntry__print(&event, 24, str2);
        SystemEntry__print_char(&event, ' ');
        SystemEntry__print_u32(&event, timeval.tv_sec, decimal);
        SystemEntry__print_char(&event, ' ');

        char str3[9];
        str3[0] = 's'; str3[1] = 'e';
        str3[2] = 'c'; str3[3] = 's';
        str3[4] = ' '; str3[5] = 'a';
        str3[6] = 'n'; str3[7] = 'd';
        str3[8] = ' ';

        SystemEntry__print(&event, 9, str3);
        SystemEntry__print_u32(&event, timeval.tv_usec, decimal);
        SystemEntry__print_char(&event, ' ');

        char str4[5];
        str4[0] = 'u'; str4[1] = 's';
        str4[2] = 'e'; str4[3] = 'c';
        str4[4] = 's';

        SystemEntry__println(&event, 5, str4);

    }

    return;

}

void __termina_app__init(int32_t * const status) {

    *status = 0;

    __termina_msg_queue__init(0, sizeof(__termina_event_t), 10, status);
    __termina_msg_queue__init(1, sizeof(TimeVal), 10, status);

    __termina_periodic_timer_connection_t connection;
    connection.type = __termina_emitter_connection_type__task;
    connection.task.task_id = 0;
    connection.task.task_msg_queue_id = 0;
    connection.task.sink_msgq_id = 1;
    connection.task.sink_port_id = 10;

    TimeVal period = {1, 0};

    __termina_periodic_timer__init(0, 0, &connection, &period, status);

    __termina_task__init(0, 10, 4096, the_task, NULL, status);

    return;

}
