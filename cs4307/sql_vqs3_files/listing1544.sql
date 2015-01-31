-- List the databases (Method 1).
psql --list

-- List the databases (Method 2, in psql).
\l

-- List the schemas.
SELECT schema_name
  FROM information_schema.schemata;

-- List the tables (Method 1).
SELECT table_name
  FROM information_schema.tables
  WHERE table_schema = '<schema_name>';

-- List the tables (Method 2, in psql).
\dt

-- Describe a table (Method 1).
SELECT *
  FROM information_schema.columns
  WHERE table_schema = '<schema_name>'
    AND table_name = '<table_name>';

-- Describe a table (Method 2, in psql).
\d <table_name>;