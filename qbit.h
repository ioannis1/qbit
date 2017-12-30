// COPYRIGHT (c) Ioannis Tambouras 2011-2015

#ifndef _QBIT
#define _QBIT

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"             /* needed for send/recv functions */
#include <math.h>
#include "utils/guc.h"
#include "../complex/complex.h"

//PG_MODULE_MAGIC;

#define MagSqr(c)  (c.x*c.x) + (c.y*c.y)
#define Mag(c)  sqrt(MagSqr(c))


typedef struct Qbit {
    Complex      up;
    Complex      down;
} Qbit;


PG_FUNCTION_INFO_V1(qbit_new);
PG_FUNCTION_INFO_V1(qbit_in);
PG_FUNCTION_INFO_V1(qbit_out);
PG_FUNCTION_INFO_V1(qbit_collapse);
PG_FUNCTION_INFO_V1(qbit_up);
PG_FUNCTION_INFO_V1(qbit_down);
PG_FUNCTION_INFO_V1(qbit_cmp);
PG_FUNCTION_INFO_V1(qbit_less);
PG_FUNCTION_INFO_V1(qbit_less_equal);
PG_FUNCTION_INFO_V1(qbit_equal);
PG_FUNCTION_INFO_V1(qbit_greater_equal);
PG_FUNCTION_INFO_V1(qbit_greater);
PG_FUNCTION_INFO_V1(qbit_guc);



#endif
