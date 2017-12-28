\timing off
SET SEARCH_PATH TO :path;
SET CLIENT_MIN_MESSAGES = 'ERROR';

DROP INDEX IF EXISTS wave_btree; 
DROP INDEX IF EXISTS wave_brin; 

CREATE INDEX wave_btree ON try (coin);
CLUSTER VERBOSE try USING wave_btree;
CREATE INDEX wave_brin ON try USING brin (coin ) WITH (pages_per_range=5);

DROP INDEX wave_btree;

