\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

set enable_seqscan = off;
--set enable_indexscan = off;
set qbit.style = 'probability';

EXPLAIN (analyze, buffers)
SELECT count(1)
FROM bank
--WHERE coin  > qbit_new(1,1,0,0);      --    100%
--WHERE coin  > qbit_new(40,2,1,2);      -- .997 
WHERE coin  > 97
--WHERE coin  > qbit_new(20,2,1,2);      -- .987 
--WHERE coin  > qbit_new(20,2,1,2);      -- .987 
--WHERE coin  > qbit_new(10,2,1,2);    -- .954
--WHERE coin  >= '(0.580,0.20j)U+(0.0,0.2j)D'::qbit
--ORDER BY coin


