-- List the schemas (users).
SELECT *
  FROM all_users;

-- List the tables.
SELECT table_name
  FROM all_tables
  WHERE owner = '<user_name>';

-- Describe a table (Method 1).
SELECT *
  FROM all_tab_columns
  WHERE owner = '<user_name>'
    AND table_name = '<table_name>';

-- Describe a table (Method 2, in sqlplus).
DESCRIBE <table_name>;