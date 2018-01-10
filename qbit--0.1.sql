--  COPYRIGHT (c) Ioannis Tambouras 2011-2015

\echo Use "CREATE EXTENSION qbit" to load this file. \quit

CREATE TYPE qbit;

CREATE OR REPLACE FUNCTION qbit_in(cstring)
    RETURNS qbit
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_out(qbit)
    RETURNS cstring
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_ket(qbit)
    RETURNS qbit
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION qbit_new(float4,float4,float4,float4)
    RETURNS qbit
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_collapse(qbit)
    RETURNS int
    AS '$libdir/qbit'
    LANGUAGE C STRICT;


CREATE TYPE qbit (
   internallength = 16,
   input          = qbit_in,
   output         = qbit_out,
 --  receive        = qbit_recv,
   --send           = qbit_send,
   alignment      = double
);


/*
CREATE OR REPLACE FUNCTION qbit_recv(internal)
   RETURNS qbit
    AS '$libdir/qbit'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_send(qbit)
   RETURNS bytea
    AS '$libdir/qbit'
   LANGUAGE C IMMUTABLE STRICT;
*/

CREATE OR REPLACE FUNCTION qbit_up(qbit)
   RETURNS float4
    AS '$libdir/qbit'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_down(qbit)
   RETURNS float4
    AS '$libdir/qbit'
   LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_cmp(qbit,qbit)
   RETURNS int
    AS '$libdir/qbit'
   LANGUAGE C IMMUTABLE STRICT;


CREATE OR REPLACE FUNCTION qbit_equal(qbit,qbit)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_less(qbit,qbit)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_less_equal(qbit,qbit)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_greater_equal(qbit,qbit)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_greater(qbit,qbit)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_upness_equal(qbit,int4)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_upness_less(qbit,int4)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_upness_less_equal(qbit,int4)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_upness_greater_equal(qbit,int4)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_upness_greater(qbit,int4)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR | (
    rightarg = qbit,
    procedure = qbit_up
);

CREATE OPERATOR ? (
    rightarg = qbit,
    procedure = qbit_collapse
);

CREATE OPERATOR < (
    leftarg    = qbit,
    rightarg   = qbit,
    procedure  = qbit_less,
    commutator = >  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);
CREATE OPERATOR <= (
    leftarg    = qbit,
    rightarg   = qbit,
    procedure  = qbit_less_equal,
    commutator = >=  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);
CREATE OPERATOR = (
    leftarg    = qbit,
    rightarg   = qbit,
    procedure  = qbit_equal,
    commutator = = ,
    restrict   = eqsel,
    join       = eqjoinsel
);
CREATE OPERATOR >= (
    leftarg    = qbit,
    rightarg   = qbit,
    procedure  = qbit_greater_equal,
    commutator = <= ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);
CREATE OPERATOR > (
    leftarg    = qbit,
    rightarg   = qbit,
    procedure  = qbit_greater,
    commutator = < ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE OPERATOR < (
    leftarg    = qbit,
    rightarg   = int4,
    procedure  = qbit_upness_less,
    commutator = >  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);
CREATE OPERATOR <= (
    leftarg    = qbit,
    rightarg   = int4,
    procedure  = qbit_upness_less_equal,
    commutator = >=  ,
    restrict   = scalarltsel,
    join       = scalarltjoinsel
);
CREATE OPERATOR = (
    leftarg    = qbit,
    rightarg   = int4,
    procedure  = qbit_upness_equal,
    commutator = = ,
    restrict   = eqsel,
    join       = eqjoinsel
);
CREATE OPERATOR >= (
    leftarg    = qbit,
    rightarg   = int4,
    procedure  = qbit_upness_greater_equal,
    commutator = <= ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);

CREATE OPERATOR > (
    leftarg    = qbit,
    rightarg   = int4,
    procedure  = qbit_upness_greater,
    commutator = < ,
    restrict   = scalargtsel,
    join       = scalargtjoinsel
);


CREATE OPERATOR CLASS qbit_ops DEFAULT FOR TYPE qbit USING btree AS 
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 >  ,
        FUNCTION 1  qbit_cmp(qbit,qbit) ;



CREATE OPERATOR CLASS qbit_minimax_ops DEFAULT FOR TYPE qbit USING brin AS
        FUNCTION 1      brin_minmax_opcinfo(internal) ,
        FUNCTION 2      brin_minmax_add_value(internal,internal,internal,internal) ,
        FUNCTION 3      brin_minmax_consistent(internal,internal,internal) ,
        FUNCTION 4      brin_minmax_union(internal,internal,internal) ,
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 > ;

CREATE OR REPLACE FUNCTION gin_extract_value_qbit(qbit,internal)
    RETURNS internal
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_extract_query_int4(qbit, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION gin_extract_query_qbit(qbit, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_extract_query_text(qbit, internal, int2, internal, internal)
    RETURNS internal
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gin_consistent_qbit(internal, int2, anyelement, int4, internal, internal)
    RETURNS bool
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION qbit_greater_text(qbit,text)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION qbit_less_text(qbit,text)
    RETURNS boolean
    AS '$libdir/qbit'
    LANGUAGE C IMMUTABLE STRICT;


CREATE OPERATOR > (
    LEFTARG   = qbit,
    RIGHTARG  = text,
    PROCEDURE = qbit_greater_text
);

CREATE OPERATOR < (
    LEFTARG   = qbit,
    RIGHTARG  = text,
    PROCEDURE = qbit_less_text
);

CREATE OPERATOR CLASS qbit_gin_ops DEFAULT FOR TYPE qbit USING gin AS
--    OPERATOR        1       < (qbit, text),
    OPERATOR        5       > (qbit, text),
    FUNCTION        1       pg_catalog.btint4cmp(integer,integer),
    FUNCTION        2       gin_extract_value_qbit(qbit, internal),
    FUNCTION        3       gin_extract_query_text(qbit, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_qbit(internal, int2, anyelement, int4, internal, internal),
STORAGE         int4;
/*
CREATE OPERATOR CLASS qbit_gin_ops DEFAULT FOR TYPE qbit USING gin AS
   OPERATOR         1       <  (qbit, int4),
    OPERATOR        2       <= (qbit, int4),
    OPERATOR        3       =  (qbit, int4),
    OPERATOR        4       >= (qbit, int4),
    OPERATOR        5       >  (qbit, int4),
    FUNCTION        1       pg_catalog.btint4cmp(integer,integer),
    FUNCTION        2       gin_extract_value_qbit(qbit, internal),
    FUNCTION        3       gin_extract_query_int4(qbit, internal, int2, internal, internal),
    FUNCTION        4       gin_consistent_qbit(internal, int2, anyelement, int4, internal, internal),
STORAGE         int4;
*/
