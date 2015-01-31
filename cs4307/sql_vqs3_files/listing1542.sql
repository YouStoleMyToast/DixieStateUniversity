-- List the databases (in db2).
LIST DATABASE DIRECTORY;

-- List the schemas.
SELECT schemaname
  FROM syscat.schemata;

-- List the tables (Method 1).
SELECT tabname
  FROM syscat.tables
  WHERE tabschema = '<schema_name>';

-- List the tables (Method 2, in db2).
LIST TABLES;

-- List the tables (Method 3, in db2).
LIST TABLES FOR SCHEMA <schema_name>;

-- Describe a table (Method 1).
SELECT *
  FROM syscat.columns
  WHERE tabname = '<table_name>'
    AND tabschema = '<schema_name>';

-- Describe a table (Method 2, in db2).
DESCRIBE TABLE <table_name> SHOW DETAIL;