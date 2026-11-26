/**
 * @file
 * @ingroup termina__osal__api
 *
 * @brief Declarations of the application functions that the transpiler
 *        generates and that the OSAL calls.
 */

#ifndef TERMINA__APP_H__
#define TERMINA__APP_H__

#include <termina/types.h>
#include <termina/prelude.h>

/**
 * @brief Initializes the application.
 * 
 * The transpiler generates this function with the initialization code of the
 * application.
 *
 * @param[out] status  Status of the initialization: `termina__error__none`, or
 *                     the code of the initialization that failed.
 */
void termina__app__init(termina__error_code_t * const status);

/**
 * @brief Initializes the global objects of the application.
 *
 * The transpiler generates this function with the initialization of the
 * fields of the global resources, tasks, handlers and emitters. It is called
 * from termina__app__init().
 */
void termina__app__init_globals(void);

/**
 * @brief Withdraws the protection of the resources and pools that the handler
 *        of `system_except` reaches.
 *
 * The transpiler generates this function only when the handler reaches one
 * of them, which `config.h` indicates with
 * `TERMINA__APP_CONFIG__EXCEPT_PROTECTED` above 0. The runtime calls it after
 * the other users have stopped and before the handler runs, so that the
 * handler takes none of their locks.
 */
void termina__app__disable_protection(void);

#endif // TERMINA__APP_H__
