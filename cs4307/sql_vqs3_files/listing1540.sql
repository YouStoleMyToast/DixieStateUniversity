-- List the databases.
exec sp_helpdb;

-- List the schemas.
SELECT schema_name
  FROM information_schema.schemata;

-- List the tables (Method 1).
SELECT *
  FROM information_schema.tables
  WHERE table_type = 'BASE TABLE'
    AND table_schema = '<schema_name>';

-- List the tables (Method 2).
exec sp_tables;

-- Describe a table (Method 1).
SELECT *
  FROM information_schema.columns
  WHERE table_catalog = '<db_name>'
    AND table_schema = '<schema_name>'
    AND table_name = '<table_name>';

-- Describe a table (Method 2).
exec sp_help <table_name>;