\timing off
SET SEARCH_PATH TO :path,public;

/*
INSERT INTO bank
SELECT --public.random_string(4)
--       i
      ( '('|| i-10 ||','|| i+20 || 'j)U+('|| i+40 || ',' || 40 ||'j)D'  )::qbit
      --, qbit_new((100*random()::float, (100*random())::int,(100*random())::int,(100*random())::int) )
FROM  generate_series(1,100,2) a(i);
*/

INSERT INTO bank
SELECT --public.random_string(4)
--       i
      ( '('|| random() ||','|| random() || 'j)U+('|| random() || ',' || random() ||'j)D'  )::qbit
      --, qbit_new((100*random()::float, (100*random())::int,(100*random())::int,(100*random())::int) )
FROM  generate_series(1,1e6) a(i);

ANALYZE bank;

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
