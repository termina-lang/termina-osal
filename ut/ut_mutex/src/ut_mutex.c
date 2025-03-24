
#include <termina.h>

void task1(void * const arg) {

    Status status;
    status.__variant = Status__Success;

    __termina_id_t port_id = 0;
    TimeVal timeval = {0, 0};
    TimeVal delay = {0, 200000U};
    TimeVal current = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

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

    __termina_sys_print.println(str);

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

        __termina_sys_print.print(str);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.println_usize(port_id, decimal);

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

        __termina_sys_print.print(str);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_u32(timeval.tv_sec, decimal);
        __termina_sys_print.print_char(' ');
        str[0] = 's'; str[1] = 'e';
        str[2] = 'c'; str[3] = 's';
        str[4] = ' '; str[5] = 'a';
        str[6] = 'n'; str[7] = 'd';
        str[8] = ' ';
        for (size_t i = 9; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.print_u32(timeval.tv_usec, decimal);
        __termina_sys_print.print_char(' ');
        str[0] = 'u'; str[1] = 's';
        str[2] = 'e'; str[3] = 'c';
        str[4] = 's';
        for (size_t i = 5; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.println(str);

        __termina_mutex__lock(0, &status);

        __termina_sys_time.clock_get_uptime(&current);

        __termina_sys_print.print_char('(');
        __termina_sys_print.print_u32(current.tv_sec, decimal);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_char(',');
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_u32(current.tv_usec, decimal);
        __termina_sys_print.print_char(')');
        __termina_sys_print.print_char(' ');
        
        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '1';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'l';
        str[10] = 'o'; str[11] = 'c';
        str[12] = 'k'; str[13] = 'e';
        str[14] = 'd'; str[15] = ' ';
        str[16] = 'm'; str[17] = 'u';
        str[18] = 't'; str[19] = 'e';
        str[20] = 'x';
        for (size_t i = 21; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.println(str);

        __termina_sys_time.delay_in(&delay);

        __termina_sys_time.clock_get_uptime(&current);
        __termina_sys_print.print_char('(');
        __termina_sys_print.print_u32(current.tv_sec, decimal);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_char(',');
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_u32(current.tv_usec, decimal);
        __termina_sys_print.print_char(')');
        __termina_sys_print.print_char(' ');

        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '1';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'r';
        str[10] = 'e'; str[11] = 'l';
        str[12] = 'e'; str[13] = 'a';
        str[14] = 's'; str[15] = 'e';
        str[16] = 'd'; str[17] = ' ';
        str[18] = 'm'; str[19] = 'u';
        str[20] = 't'; str[21] = 'e';
        str[22] = 'x';
        for (size_t i = 23; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.println(str);

        __termina_mutex__unlock(0, &status);

    }

    return;

}

void task2(void * const arg) {

    Status status;
    status.__variant = Status__Success;

    TimeVal delay = {0, 500000U};
    TimeVal current = {0, 0};

    SysPrintBase decimal;
    decimal.__variant = SysPrintBase__Decimal;

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

    __termina_sys_print.println(str);

    for (;;) {

        __termina_mutex__lock(0, &status);
        __termina_sys_time.clock_get_uptime(&current);

        __termina_sys_print.print_char('(');
        __termina_sys_print.print_u32(current.tv_sec, decimal);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_char(',');
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_u32(current.tv_usec, decimal);
        __termina_sys_print.print_char(')');
        __termina_sys_print.print_char(' ');
        
        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '2';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'l';
        str[10] = 'o'; str[11] = 'c';
        str[12] = 'k'; str[13] = 'e';
        str[14] = 'd'; str[15] = ' ';
        str[16] = 'm'; str[17] = 'u';
        str[18] = 't'; str[19] = 'e';
        str[20] = 'x';
        for (size_t i = 21; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.println(str);

        __termina_sys_time.delay_in(&delay);

        __termina_sys_time.clock_get_uptime(&current);

        __termina_sys_time.clock_get_uptime(&current);
        __termina_sys_print.print_char('(');
        __termina_sys_print.print_u32(current.tv_sec, decimal);
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_char(',');
        __termina_sys_print.print_char(' ');
        __termina_sys_print.print_u32(current.tv_usec, decimal);
        __termina_sys_print.print_char(')');
        __termina_sys_print.print_char(' ');

        str[0] = 'T'; str[1] = 'a';
        str[2] = 's'; str[3] = 'k';
        str[4] = ' '; str[5] = '2';
        str[6] = ' '; str[7] = '-';
        str[8] = ' '; str[9] = 'r';
        str[10] = 'e'; str[11] = 'l';
        str[12] = 'e'; str[13] = 'a';
        str[14] = 's'; str[15] = 'e';
        str[16] = 'd'; str[17] = ' ';
        str[18] = 'm'; str[19] = 'u';
        str[20] = 't'; str[21] = 'e';
        str[22] = 'x';
        for (size_t i = 23; i < __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE; i = i + 1) {
            str[i] = '\0';
        }
        __termina_sys_print.println(str);

        __termina_mutex__unlock(0, &status);
    }

}

void __termina_app__init(Status * const status) {

    status->__variant = Status__Success;

    __termina_sys_time__init();
    __termina_sys_print__init();

    __termina_mutex__init(0, sizeof(__termina_id_t), 8, status);

    __termina_msg_queue__init(0, sizeof(__termina_id_t), 10, status);
    __termina_msg_queue__init(1, sizeof(TimeVal), 10, status);

    __termina_periodic_timer_connection_t connection;
    connection.type = __TerminaEmitterConnectionType__Task;
    connection.task.task_msgq_id = 0;
    connection.task.sink_msgq_id = 1;
    connection.task.sink_port_id = 0;

    TimeVal period = {1, 0};

    __termina_periodic_timer__init(0, &connection, &period, status);

    __termina_task__init(0, 8, 4096, task1, NULL, status);
    __termina_task__init(1, 10, 4096, task2, NULL, status);

    return;

}
