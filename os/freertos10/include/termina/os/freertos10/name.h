/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Generation of the four-character names of the FreeRTOS objects.
 */

#ifndef TERMINA__OS__FREERTOS10__NAME_H__
#define TERMINA__OS__FREERTOS10__NAME_H__

#include <termina.h>

/**
 * @brief Advances a four-character object name to the next one.
 *
 * The names start at `0000`. `c3` and `c4` run from `0` to `9`. `c2` advances
 * through the ASCII codes up to `z` and then restarts at `a`, and `c1`
 * advances through the ASCII codes up to `z`. Advancing past `zz99` reboots
 * the system.
 *
 * @param c1  First character of the name.
 * @param c2  Second character of the name.
 * @param c3  Third character of the name.
 * @param c4  Fourth character of the name.
 */
#define NEXT_OBJECT_NAME(c1, c2, c3, c4)             \
    do {                                             \
        if (c4 == '9') {                             \
            if (c3 == '9') {                         \
                if (c2 == 'z') {                     \
                    if (c1 == 'z') {                 \
                        termina__exec__reboot();  \
                    } else {                         \
                        c1++;                        \
                    }                                \
                    c2 = 'a';                        \
                } else {                             \
                    c2++;                            \
                }                                    \
                c3 = '0';                            \
            } else {                                 \
                c3++;                                \
            }                                        \
            c4 = '0';                                \
        }                                            \
        else {                                       \
            c4++;                                    \
        }                                            \
    } while (0)


#endif // TERMINA__OS__FREERTOS10__NAME_H__