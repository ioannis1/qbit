EXTENSION = qbit             # the extensions name
DATA      = qbit--0.1.sql 
REGRESS   = qbit_test        # our test script file (without extension)
MODULES   = qbit             # our c module file to build
#.DEFAULT_GOAL = s

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

vi:
	 vi ~postgres/src/postgres/src/tutorial/complex.c
ins:
	sudo -u postgres make install
i drop:
	psql -qX -h localhost -d contrib_regression -U postgres  < $@.sql
c:
	PGUSER=postgres sudo -E  make  installcheck
pgxs:
	vi $(PGXS)
pg:
	PGOPTIONS=--search_path=wave,public psql lessons
