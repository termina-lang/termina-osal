#ifndef __CONFIG_H__
#define __CONFIG_H__

#define __TERMINA_APP_CONFIG_POOLS 0

#define __TERMINA_APP_CONFIG_TASKS 2

#define __TERMINA_APP_CONFIG_PERIODIC_TIMERS 1

#define __TERMINA_APP_CONFIG_MUTEXES 1

#define __TERMINA_APP_CONFIG_MESSAGE_QUEUES 2

#define __TERMINA_APP_CONFIG_MESSAGE_BUFFER_MEMORY \
    (__TERMINA_APP_CONFIG_MESSAGE_QUEUE_BUFFER(10, sizeof(__termina_id_t))) + \
    (__TERMINA_APP_CONFIG_MESSAGE_QUEUE_BUFFER(10, sizeof(TimeVal)))

#define __TERMINA_MICROSECONDS_PER_TICK 10000

#define __TERMINA_CONFIG_SYS_PRINT_BUFFER_SIZE 256

#endif // __CONFIG_H__
