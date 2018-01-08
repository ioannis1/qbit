\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

--set enable_seqscan = off;
set qbit.style = 'polar';

EXPLAIN (analyze, buffers)
SELECT coin
FROM bank
WHERE coin  >= '(0.580,0.20j)U+(0.0,0.2j)D'::qbit
ORDER BY coin


