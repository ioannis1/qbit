-- complain if script is sourced in psql, rather than via CREATE EXTENSION
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

CREATE OR REPLACE FUNCTION qbit_out_prob(qbit)
    RETURNS cstring
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


CREATE OPERATOR CLASS qbit_ops DEFAULT FOR TYPE qbit USING btree AS 
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 >  ,
        FUNCTION 1  qbit_cmp(qbit,qbit)
;



CREATE OPERATOR CLASS qbit_minimax_ops DEFAULT FOR TYPE qbit USING brin AS
        FUNCTION 1      brin_minmax_opcinfo(internal) ,
        FUNCTION 2      brin_minmax_add_value(internal,internal,internal,internal) ,
        FUNCTION 3      brin_minmax_consistent(internal,internal,internal) ,
        FUNCTION 4      brin_minmax_union(internal,internal,internal) ,
        OPERATOR 1 <  ,
        OPERATOR 2 <= ,
        OPERATOR 3 =  ,
        OPERATOR 4 >= ,
        OPERATOR 5 >
;
