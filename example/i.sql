\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

--set enable_seqscan = off;

EXPLAIN (analyze, buffers)
SELECT coin
FROM bank
WHERE coin  > '(1,1j)U+(0,0j)D'::qbit
