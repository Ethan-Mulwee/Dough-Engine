#ifndef DOUGH_PRECISION_H
#define DOUGH_PRECISION_H

#include <float.h>

namespace dough {
    typedef float real;

    #define real_sqrt sqrtf
    #define real_pow powf
    #define real_abs fabsf
    #define REAL_MAX DBL_MAX
}

#endif