\timing off
SET SEARCH_PATH TO :path,public;


INSERT INTO try
SELECT --public.random_string(4)
       i
     --, ( '('|| i ||','|| i || 'j)U+('|| i || ',' || i ||'j)D'  )::qbit
      , qbit_new(i,i,i,i)
FROM  generate_series(1,100000) a(i);

ANALYZE try;

\q


\COPY try FROM stdin;
1	(1,3)
2	(2,4)
\.

\q

INSERT INTO wave.try values(1,'(1,2j)U+(2,3)D'::qbit);
INSERT INTO wave.try values(2,'(11,20j)U+(2003,3002j)D'::qbit);
insert into wave.try values(3,'(1,2j)U+(2,2j)D'::qbit);
select * from try;
\q
