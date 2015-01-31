-- List the databases (Method 1).
SELECT schema_name
  FROM information_schema.schemata;

-- List the databases (Method 2, in mysql).
SHOW DATABASES;

-- List the tables (Method 1).
SELECT table_name
  FROM information_schema.tables
  WHERE table_schema = '<db_name>';

-- List the tables (Method 2, in mysql).
SHOW TABLES;

-- Describe a table (Method 1).
SELECT *
  FROM information_schema.columns
  WHERE table_schema = '<db_name>'
    AND table_name = '<table_name>';

-- Describe a table (Method 2, in mysql).
DESCRIBE <table_name>;