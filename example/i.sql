\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

--set enable_seqscan = off;
set enable_indexscan = off;
set qbit.style = 'probability';

--EXPLAIN (analyze, buffers)
SELECT coin
FROM bank
WHERE coin  > 50
--WHERE coin  >= '(0.580,0.20j)U+(0.0,0.2j)D'::qbit
--ORDER BY coin


