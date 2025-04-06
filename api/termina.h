#ifndef __TERMINA_H__
#define __TERMINA_H__

/* Application configuration options */
#include "config.h"

/* termina common types */
#include <termina/types.h>

/* Termina operating system-dependent types */
#include <termina/prelude.h>

/* Termina resource locking interface */
#include <termina/lock.h>

/* Termina pool management interface */
#include <termina/pool.h>

/* Termina message queue management interface */
#include <termina/task.h>

/* Termina message queue management interface */
#include <termina/msg_queue.h>

/* Termina periodic timer management interface */
#include <termina/periodic_timer.h>

/* Termina interrupt management interface */
#include <termina/interrupt.h>

/* Termina application interface */
#include <termina/app.h>

/* Termina executive interface */
#include <termina/exec.h>

/* Termina System API */
#include <termina/system/system.h>
#include <termina/system/sys_time.h>
#include <termina/system/sys_print.h>

#endif // __TERMINA_H__
