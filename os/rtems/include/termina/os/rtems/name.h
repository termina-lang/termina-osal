/**
 * @file
 * @ingroup termina__osal__os
 *
 * @brief Generation of the four-character names of the RTEMS objects.
 */

#ifndef TERMINA__OS__RTEMS__NAME_H__
#define TERMINA__OS__RTEMS__NAME_H__

#include <termina.h>

/**
 * @brief Advances a four-character object name to the next one.
 *
 * `c1` and `c2` run from `a` to `z`, and `c3` and `c4` from `0` to `9`. When
 * the names run out, the system reboots.
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


#endif // TERMINA__OS__RTEMS__NAME_H__