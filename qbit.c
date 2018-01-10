// COPYRIGHT (c) Ioannis Tambouras 2011-2015

#include "qbit.h"

PG_FUNCTION_INFO_V1(qbit_greater_text);
PG_FUNCTION_INFO_V1(gin_extract_query_text);

Datum
gin_extract_value_qbit(PG_FUNCTION_ARGS)
{
        Qbit       *item     = (Qbit *)  PG_GETARG_POINTER(0);
        int32      *nentries = (int32 *)  PG_GETARG_POINTER(1);
        Datum      *entries  = (Datum *) palloc(sizeof(Datum) * 1);
	int32      upness;

	upness     = (int32) round(100*qbit_up_internal(item) );
        entries[0] = Int32GetDatum( upness );
        *nentries  = 1;
        PG_RETURN_POINTER(entries);
}

Datum
create_elem(int32 i)
{
      PG_RETURN_INT32(i);
}

Datum
gin_extract_query_text(PG_FUNCTION_ARGS)
{
        text                *val = (text *) PG_GETARG_TEXT_PP(1);
        int32          *nentries = (int32 *) PG_GETARG_POINTER(1);
        StrategyNumber  strategy = PG_GETARG_UINT16(2);
        int32           probab, size; 
        Datum           *items   = NULL;
        char            *str;
       
        str     = VARDATA_ANY(val);
        probab = atoi(str);
	if (probab>100) probab=100;
	if (probab<0)   probab=0;

        *nentries   = 0;
        switch (strategy)
        {
            case 5 : size  =   101  -  probab;
                     items = (Datum *) palloc(sizeof(Datum)* size);
                     for (int i= probab; i<=100; i++)  {
                              items[*nentries] = create_elem( i);
                             *nentries        += 1;
                     }
                     break;
        }
        PG_RETURN_POINTER(items);
}

Datum
gin_extract_query_int4(PG_FUNCTION_ARGS)
{
        int32          probab     =  PG_GETARG_INT32(0);
        int32          *nentries = (int32 *) PG_GETARG_POINTER(1);

        Datum           *items ;
        int32           size;
        StrategyNumber  strategy = PG_GETARG_UINT16(2);

	if (probab>100) probab=100;
	if (probab<0)   probab=0;

        *nentries   = 0;
        switch (strategy)
        {
            case 3 : items = (Datum *) palloc(sizeof(Datum));
                     items[0]  = create_elem(  probab );
                     *nentries = 1;
                     break;

            case 2 : size  =   probab +1;
                     items = (Datum *) palloc(sizeof(Datum)* size);
                     for (int i=0; i<= probab; i++)  {
                              items[i]   = create_elem( i);
                             *nentries  += 1;
                     }
                     break;

            case 1 : size  =   probab +1;
                     items = (Datum *) palloc(sizeof(Datum)* size);
                     for (int i=0; i< probab; i++)  {
                              items[i]  = create_elem(i);
                             *nentries += 1;
                     }
                     break;

            case 4 : size  =   101 - probab;
                     items = (Datum *) palloc(sizeof(Datum)* size);
                     for (int i=probab; i<=100; i++)  {
                              items[*nentries] = create_elem(i);
                             *nentries        += 1;
                     }
                     break;

            case 5 : size  =   100  -  probab;
                     items = (Datum *) palloc(sizeof(Datum)* size);
                     for (int i= probab+1; i<=100; i++)  {
                              items[*nentries] = create_elem( i);
                             *nentries        += 1;
                     }
                     break;
        }
        PG_RETURN_POINTER(items);
}

Datum
gin_extract_query_qbit(PG_FUNCTION_ARGS)
{
        Qbit           *query    = (Qbit *)  PG_GETARG_POINTER(0);
        int32          *nentries = (int32 *) PG_GETARG_POINTER(1);
        Datum           *items ;
        int32           size;
        StrategyNumber  strategy = PG_GETARG_UINT16(2);

        *nentries   = 0;
        switch (strategy)
        {
            case 3 : items = (Datum *) palloc(sizeof(Datum));
                     items[0]  = create_elem( round( (int) round( 100*qbit_up_internal(query) )));
                     *nentries   = 1;
                     break;
            case 2 : size     =   1 + ((int) round( 100*qbit_up_internal(query) ));
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=0;i<= (int) round( 100*qbit_up_internal(query) ); i++)  {
                              items[i] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;
            case 1 : size     =  1 + ((int) round(100*qbit_up_internal(query) ));
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=0;i< (int) round(100*qbit_up_internal(query)); i++)  {
                              items[i] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;
            case 4 : size     =   101 - ((int) round(100*qbit_up_internal(query) ));
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=(int)round(100*qbit_up_internal(query));i<=90; i++)  {
                              items[*nentries] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;
            case 5 : size     =   101 - ((int) round(100*qbit_up_internal(query) ));
                     items = (Datum *) palloc(sizeof(Datum)* size);

                     for (int i=((int)round(100*qbit_up_internal(query)))+1;i<=90; i++)  {
                              items[*nentries] = create_elem( (int) i);
                             *nentries   += 1;
                     }
                     break;

        }
        PG_RETURN_POINTER(items);
}

Datum
gin_consistent_qbit(PG_FUNCTION_ARGS)
{
        bool           *recheck = (bool *) PG_GETARG_POINTER(5);

        *recheck = true;
        PG_RETURN_BOOL(true);
}


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
                 errmsg("valid syntax is \"(2,3j)U+(1,2j)D\"")));

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



Datum
qbit_out(PG_FUNCTION_ARGS)
{
    Qbit       *q = (Qbit *) PG_GETARG_POINTER(0);
    char       *result;
    float4     a_angle, b_angle;

    if (! strcmp( GetConfigOption("qbit.style",true,false), "probability") ) {
        result = psprintf("(%.2f)U+(%.2f)D", MagSqr(q->up), MagSqr(q->down) );
    } else if (! strcmp( GetConfigOption("qbit.style",true,false), "polar") ) {
               a_angle  =  (180/3.14159)* atan(q->up.y/q->up.x);
               b_angle  =  (180/3.14159)* atan(q->down.y/q->down.x);
 
        result = psprintf("%.2f<%.2f>U+%.2f<%.2f>D",
                 Mag(q->up), a_angle, Mag(q->down), b_angle );
    }else{
        result = psprintf("(%.3f,%.3fj)U+(%.3f,%.3fj)D", q->up.x, q->up.y, q->down.x, q->down.y);
    }
    PG_RETURN_CSTRING(result);
}





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

static float4
qbit_up_internal(Qbit *q) 
{
    Complex       up ;
    const char   *guc ;
    float4        longitude,  latitude;
    //float4        angle;

    guc  = GetConfigOption("qbit.geo",true,false);

    if (NULL != guc) {
         if (sscanf(guc, "%f N  / %f W", &latitude, &longitude) != 2) 
                  elog(ERROR, "expected something like qbit.geo=\'47 N / 122 W\' \n");
    }else{
         latitude = 90;
    }


     up.x   =  (q->up.x * q->up.x) + (q->up.y*q->up.y)  ;
     //up.x   = sqrt( (q->up.x * q->up.x) + (q->up.y*q->up.y)  );
     //up.y   =  (180/3.14159)* atan(up.y/up.x);

     //angle   = latitude - up.y;
     //return cos (angle * (3.14159/180) );
     //return MAG_SQUARED(q->up);
     return up.x ;
}

Datum
qbit_up(PG_FUNCTION_ARGS)
{ 
    Qbit   *q     = (Qbit *) PG_GETARG_POINTER(0);
    PG_RETURN_FLOAT4( qbit_up_internal(q) );
}

Datum
qbit_down(PG_FUNCTION_ARGS)
{ 
    Qbit   *q     = (Qbit *) PG_GETARG_POINTER(0);
    PG_RETURN_FLOAT4(1 - qbit_up_internal(q) );
}



static int
qbit_cmp_internal( Qbit *a, Qbit *b ) 
{
     float4   amag = MagSqr(a->up),  bmag=MagSqr(b->up);

     if ( amag == bmag ) return 0 ;
     if ( amag < bmag  ) return -1;
     return 1 ;
}

Datum
qbit_cmp(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);

        PG_RETURN_INT32( qbit_cmp_internal(a,b) );
}


Datum
qbit_less(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) == -1 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_less_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) <= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) == 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_greater_equal(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) >= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_greater(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *b = (Qbit *) PG_GETARG_POINTER(1);
        
        if (qbit_cmp_internal(a,b) > 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}

Datum
qbit_ket(PG_FUNCTION_ARGS)
{
        Qbit    *a = (Qbit *) PG_GETARG_POINTER(0);
        Qbit    *result;

        result  = (Qbit *) palloc(sizeof(Qbit));
        result->up.x    =  a->up.x ;
        result->up.y    = -1 * a->up.y ;
        result->down.x  =  a->up.x ;
        result->down.y  = -1 * a->down.y ;

        PG_RETURN_POINTER(result);
}

static int
qbit_upness_cmp_internal( Qbit *a, int32 b )
{
     // compare probabilities
     float4   amag = 100 * ( (a->up.x*a->up.x)+(a->up.y*a->up.y));

     if ( amag == b  ) return 0 ;
     if ( amag  < b  ) return -1;
     return 1 ;
}
Datum
qbit_upness_less(PG_FUNCTION_ARGS)
{
        Qbit      *a = (Qbit *) PG_GETARG_POINTER(0);
        int32      b = PG_GETARG_INT32(1);

        if (qbit_upness_cmp_internal(a,b) < 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_upness_less_equal(PG_FUNCTION_ARGS)
{
        Qbit      *a = (Qbit *) PG_GETARG_POINTER(0);
        int32      b = PG_GETARG_INT32(1);

        if (qbit_upness_cmp_internal(a,b) <= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_upness_equal(PG_FUNCTION_ARGS)
{
        Qbit      *a = (Qbit *) PG_GETARG_POINTER(0);
        int32      b = PG_GETARG_INT32(1);

        if (qbit_upness_cmp_internal(a,b) == 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_upness_greater_equal(PG_FUNCTION_ARGS)
{
        Qbit      *a = (Qbit *) PG_GETARG_POINTER(0);
        int32      b = PG_GETARG_INT32(1);

        if (qbit_upness_cmp_internal(a,b) >= 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}
Datum
qbit_upness_greater(PG_FUNCTION_ARGS)
{
        Qbit      *a = (Qbit *) PG_GETARG_POINTER(0);
        int32      b = PG_GETARG_INT32(1);

        if (qbit_upness_cmp_internal(a,b) > 0 ) PG_RETURN_BOOL(true);
        PG_RETURN_BOOL(false);
}


Datum
qbit_greater_text(PG_FUNCTION_ARGS)
{
        Qbit     *a = (Qbit *) PG_GETARG_POINTER(0);
        text   *val = (text *) PG_GETARG_TEXT_PP(1);

        char   *str = VARDATA_ANY(val);
        PG_RETURN_BOOL( (100* qbit_up_internal(a)) > atoi(str)  );
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

