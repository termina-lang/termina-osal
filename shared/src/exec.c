
/**
 * @file
 * @ingroup termina__osal__shared
 *
 * @brief Handover of the system to software outside Termina.
 */

#include <termina.h>
#include <termina/shared/exec.h>

void termina__exec__handover(void) {

    termina__os__exec__quiesce();

}
