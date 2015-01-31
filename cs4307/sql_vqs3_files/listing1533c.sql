SELECT title_id, type, sales
  FROM titles
  TABLESAMPLE SYSTEM (25);