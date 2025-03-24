#ifndef __TERMINA__OS__RTEMS5__NAME_H__
#define __TERMINA__OS__RTEMS5__NAME_H__

#include <termina.h>

#define NEXT_OBJECT_NAME(c1, c2, c3, c4)             \
    do {                                             \
        if (c4 == '9') {                             \
            if (c3 == '9') {                         \
                if (c2 == 'z') {                     \
                    if (c1 == 'z') {                 \
                        __termina_exec__shutdown(1); \
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


#endif // __TERMINA__OS__RTEMS5__NAME_H__