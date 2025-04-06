
#include <termina.h>

void the_task(void * const arg) {

    Status status;
    status.__variant = Status__Success;

    __termina_id_t port_id = 0;

    TimeVal timeval = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

    char str[__TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE];

    for (;;) {
        __termina_msg_queue__recv(0, &port_id, &status);
        __termina_msg_queue__recv(1, &timeval, &status);

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
        for (size_t i = 25; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }

        SystemEntry__print(str);
        SystemEntry__print_char(' ');
        SystemEntry__println_usize(port_id, decimal);

        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '1';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'R';
        str[10] = 'e'; str[11] = 'c';
        str[12] = 'e'; str[13] = 'i';
        str[14] = 'v'; str[15] = 'e';
        str[16] = 'd'; str[17] = ' ';
        str[18] = 't'; str[19] = 'i';
        str[20] = 'm'; str[21] = 'e';
        str[22] = ':';
        str[23] = ' ';
        for (size_t i = 24; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }

        SystemEntry__print(str);
        SystemEntry__print_char(' ');
        SystemEntry__print_u32(timeval.tv_sec, decimal);
        SystemEntry__print_char(' ');
        str[0] = 's'; str[1] = 'e';
        str[2] = 'c'; str[3] = 's';
        str[4] = ' '; str[5] = 'a';
        str[6] = 'n'; str[7] = 'd';
        str[8] = ' ';
        for (size_t i = 9; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        SystemEntry__print_u32(timeval.tv_usec, decimal);
        SystemEntry__print_char(' ');
        str[0] = 'u'; str[1] = 's';
        str[2] = 'e'; str[3] = 'c';
        str[4] = 's';
        for (size_t i = 5; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        SystemEntry__println(str);

    }

    return;

}

void __termina_app__init(Status * const status) {

    status->__variant = Status__Success;

    __termina_msg_queue__init(0, sizeof(__termina_id_t), 10, status);
    __termina_msg_queue__init(1, sizeof(TimeVal), 10, status);

    __termina_periodic_timer_connection_t connection;
    connection.type = __TerminaEmitterConnectionType__Task;
    connection.task.task_msg_queue_id = 0;
    connection.task.sink_msgq_id = 1;
    connection.task.sink_port_id = 0;

    TimeVal period = {1, 0};

    __termina_periodic_timer__init(0, &connection, &period, status);

    __termina_task__init(0, 10, 4096, the_task, NULL, status);

    return;

}
