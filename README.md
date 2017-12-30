# COPYRIGHT (c) Ioannis Tambouras 2011-2015

Every qbit is automatically normalised.
Set the GUC parameter qbit.style='probability' to show probabilities instead of  complex coefficients.
Set the GUC parameter qbit.style='polar' to show complex coefficients in polar form.

# Constructors

SELECT '(1,2j)U+(3,4)D'::qbit                  =>  (0.183,0.365j)U+(0.548,0.730j)D 

SELECT qbit_new(1,2,3,4)                       =>  (0.183,0.365j)U+(0.548,0.730j)D 

# Operations

SELECT  qbit_collapse( '(1,2j)U+(3,4)D' )      =>  either 0 or 1

SELECT  qbit_up( '(1,2j)U+(3,4)D' )            =>  0.166667      probability  for U state


# Relational comparisons

SELECT qbit_cmp('(1,2j)U+(3,4)D' , '(2,2j)U+(1,2j)D' )         =>   -1

SELECT '(1,2j)U+(3,4)D' <   '(2,2j)U+(1,2j)D'::qbit            =>   true

SELECT '(1,2j)U+(3,4)D' <=  '(2,2j)U+(1,2j)D'::qbit            =>   true

SELECT '(1,2j)U+(3,4)D' > '(2,2j)U+(1,2j)D'::qbit              =>   false

SELECT '(1,2j)U+(3,4)D' >= '(2,2j)U+(1,2j)D'::qbit             =>   false

SELECT '(1,2j)U+(3,4)D' = '(1,2j)U+(3,4j)D'::qbit              =>  true
