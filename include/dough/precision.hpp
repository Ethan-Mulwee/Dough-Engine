#ifndef DOUGH_PRECISION_H
#define DOUGH_PRECISION_H

#include <math.h>
#include <float.h>

namespace dough {
    typedef float real;

    #define real_sqrt sqrtf
    #define real_pow powf
    #define real_abs fabsf
    #define REAL_MAX DBL_MAX

    /** Defines the number e on which 1+e == 1 **/
    //???
    #define real_epsilon FLT_EPSILON
}

#endif