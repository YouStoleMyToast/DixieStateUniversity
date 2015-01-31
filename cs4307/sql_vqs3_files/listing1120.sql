CREATE GLOBAL TEMPORARY TABLE titles2 AS
  SELECT title_name, sales
    FROM titles
    WHERE pub_id = 'P01';