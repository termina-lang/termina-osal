#ifndef TERMINA_H__
#define TERMINA_H__

/* Application configuration options */
#include "config.h"

/* termina common types */
#include <termina/types.h>

/* Termina floating point types and bit reinterpretation */
#include <termina/float.h>

/* Termina operating system-dependent types */
#include <termina/prelude.h>

/* Termina run-time check interface */
#include <termina/check.h>

/* Termina resource locking interface */
#include <termina/lock.h>

/* Termina mutex interface */
#include <termina/mutex.h>

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

/* Termina exception management */
#include <termina/except.h>

/* Termina System API */
#include <termina/system/system.h>
#include <termina/system/sys_time.h>
#include <termina/system/sys_print.h>
#include <termina/system/sys_read.h>

#endif // TERMINA_H__
