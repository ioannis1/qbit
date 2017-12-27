SET CLIENT_MIN_MESSAGES = 'ERROR';
SET SEARCH_PATH to public;
BEGIN;

SELECT '(1.01,2.0j)U+(2.003,3.002j)D'::qbit;
SELECT '(11,20j)U+(2003,3002j)D'::qbit;
SELECT qbit_up('(1,2j)U+(2,3j)D'::qbit);
SELECT qbit_cmp('(1,2j)U+(2,3j)D'::qbit,  '(1,2j)U+(1,2j)D');
SELECT qbit_cmp('(1,3j)U+(2,3j)D'::qbit,  '(1,2j)U+(1,2j)D');
SELECT qbit_cmp('(1,-3j)U+(2,3j)D'::qbit,  '(1,2j)U+(1,2j)D');
SELECT qbit_cmp('(1,-3j)U+(2,3j)D'::qbit,  '(1,22j)U+(1,2j)D');

select qbit_new(1,2,3,4);

\q
select wave
FROM try
WHERE wave > '(12,2j)U+(3,5j)D'
\q



