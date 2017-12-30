-- COPYRIGHT (c) Ioannis Tambouras 2011-2015

CREATE EXTENSION qbit;

SELECT '[1,2U __ 2,3D']::qbit;

\q
SELECT '(1,2)'::qbit +   '(1,2)';
SELECT '(1,2)'::qbit -   '(1,2)';
SELECT '(1,2)'::qbit =   '(1,2)';
SELECT '(1,2)'::qbit >   '(0,2)';
SELECT '(1,2)'::qbit >=  '(8,2)';

SELECT mag( '(3,4)'::qbit );
SELECT qbit_mag_squared( '(3,4)'::qbit );

SELECT  2 > '(3,4)'::qbit;
SELECT 25 >= '(3,4)'::qbit;

SELECT  ('(1,8)'::qbit@);      -- qbit conjugate
SELECT |'(3,4)'::qbit ;        -- magnitude

SELECT qbit_new(1,8);
SELECT qbit_new(3,1);

SELECT qbit_real('(-2,3)'::qbit);
SELECT qbit_img('(2,-3)'::qbit);

SELECT qbit_overlaps('(2,2)'::qbit, '(1,1)');
SELECT qbit_overlaps('(2,2)'::qbit, '(3,2)');

