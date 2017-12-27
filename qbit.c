#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"             /* needed for send/recv functions */
#include <math.h>

PG_MODULE_MAGIC;

typedef struct Complex {
    float4      x;
    float4      y;
} Complex;

typedef struct Qbit {
    Complex      up;
    Complex      down;
} Qbit;



#define MagSqr(c)  (c.x*c.x) + (c.y*c.y)

PG_FUNCTION_INFO_V1(qbit_new);
Datum
qbit_new(PG_FUNCTION_ARGS)
{
    float4      a1 = PG_GETARG_FLOAT4(0);
    float4      a2 = PG_GETARG_FLOAT4(1);
    float4      b1 = PG_GETARG_FLOAT4(2);
    float4      b2 = PG_GETARG_FLOAT4(3);
    float4      inner_product;

    Qbit       *result;

    result  =  (Qbit*) palloc(sizeof(Qbit));

    result->up.x    = a1 ;
    result->up.y    = a2 ;
    result->down.x  = b1 ;
    result->down.y  = b2 ;
    inner_product = sqrt( MagSqr(result->up) + MagSqr(result->down));

    result->up.x    = a1 /inner_product ;
    result->up.y    = a2 /inner_product ;
    result->down.x  = b1 /inner_product ;
    result->down.y  = b2 /inner_product ;


    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(qbit_in);

Datum
qbit_in(PG_FUNCTION_ARGS)
{
    char       *str = PG_GETARG_CSTRING(0);
    float4      a1, a2, b1, b2;
    Qbit       *result;
    float4      inner_product;


    if (sscanf(str, " (%f,%fj)U+(%f,%fj)D ", &a1, &a2, &b1, &b2) != 4)
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for qbit: \"%s\"",
                        str)));

    result  =  (Qbit*) palloc(sizeof(Qbit));

    result->up.x    = a1 ;
    result->up.y    = a2 ;
    result->down.x  = b1 ;
    result->down.y  = b2 ;
    inner_product   = sqrt( MagSqr(result->up) + MagSqr(result->down));
    result->up.x    = a1 /inner_product ;
    result->up.y    = a2 /inner_product ;
    result->down.x  = b1 /inner_product ;
    result->down.y  = b2 /inner_product ;


    PG_RETURN_POINTER(result);
}


PG_FUNCTION_INFO_V1(qbit_out);

Datum
qbit_out(PG_FUNCTION_ARGS)
{
    Qbit       *q = (Qbit *) PG_GETARG_POINTER(0);
    char       *result;
    result = psprintf("(%.3f,%.3fj)U+(%.3f,%.3fj)D", q->up.x, q->up.y, q->down.x, q->down.y);
    PG_RETURN_CSTRING(result);
}


PG_FUNCTION_INFO_V1(qbit_collapse);

Datum
qbit_collapse(PG_FUNCTION_ARGS)
{
    Qbit      *q     = (Qbit *) PG_GETARG_POINTER(0);
    int32     random = rand()%100 + 1;

    if (random < ( 100*MagSqr(q->up))) {
            PG_RETURN_INT32(1);
    }
    PG_RETURN_INT32(0);
}
/*
Datum
qbit_collapse(PG_FUNCTION_ARGS)
{
    Qbit      *q     = (Qbit *) PG_GETARG_POINTER(0);
    int32     random = rand()%100;
    int32    up_size = VARSIZE_ANY_EXHDR("UP");
    int32    down_size = VARSIZE_ANY_EXHDR("DOWN");
    int32    text_size ;
    text     *msg;


    if (random < ( MagSqr(q->up))) {
            text_size = up_size + VARHDRSZ;
            msg       = (text *) palloc(text_size);
            SET_VARSIZE( msg, text_size);
            memcpy(VARDATA(msg) + down_size, VARDATA_ANY("UP"), up_size);
            PG_RETURN_TEXT_P(msg);
    }
    text_size = down_size + VARHDRSZ;
    msg       = (text *) palloc(text_size);
    SET_VARSIZE( msg, text_size);
    memcpy(VARDATA(msg), VARDATA_ANY("DOWN"), down_size);
    PG_RETURN_TEXT_P(msg);
}
*/



PG_FUNCTION_INFO_V1(qbit_up);

Datum
qbit_up(PG_FUNCTION_ARGS)
{
    Qbit      *q     = (Qbit *) PG_GETARG_POINTER(0);
    float4    result = MagSqr(q->up);

    PG_RETURN_FLOAT4(result );
}

static int
qbit_cmp_internal( Qbit *a, Qbit *b ) 
{
     float4   amag = MagSqr(a->up),  bmag=MagSqr(b->up);
     if ( amag < bmag  ) return -1;
     if ( amag == bmag ) return 0 ;
     return 1 ;
}

PG_FUNCTION_INFO_V1(qbit_cmp);
Datum
qbit_cmp(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        PG_RETURN_INT32( qbit_cmp_internal(a,b) );
}


PG_FUNCTION_INFO_V1(qbit_less);

Datum
qbit_less(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) == -1 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

PG_FUNCTION_INFO_V1(qbit_less_equal);

Datum
qbit_less_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) <= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


PG_FUNCTION_INFO_V1(qbit_equal);

Datum
qbit_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) == 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

PG_FUNCTION_INFO_V1(qbit_greater_equal);

Datum
qbit_greater_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) >= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

PG_FUNCTION_INFO_V1(qbit_greater);

Datum
qbit_greater(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) > 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
/*
PG_FUNCTION_INFO_V1(qbit_recv);
Datum
qbit_recv(PG_FUNCTION_ARGS)
{
    StringInfo  buf = (StringInfo) PG_GETARG_POINTER(0);
    Complex    *up,*down;
    Qbit       *q;

    result = (Complex *) palloc(sizeof(Complex));
    result->x = pq_getmsgfloat8(buf);
    result->y = pq_getmsgfloat8(buf);
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(complex_send);

Datum
complex_send(PG_FUNCTION_ARGS)
{
    Complex    *complex = (Complex *) PG_GETARG_POINTER(0);
    StringInfoData buf;
    pq_begintypsend(&buf);
    pq_sendfloat8(&buf, complex->x);
    pq_sendfloat8(&buf, complex->y);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}
*/

