\timing off
SET SEARCH_PATH TO  :path,public;
SET CLIENT_MIN_MESSAGES = 'ERROR';
begin;

explain (analyze, buffers)
SELECT wave
FROM try
WHERE wave < '(12,2j)U+(3,5j)D'

