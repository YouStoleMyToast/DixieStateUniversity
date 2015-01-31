SELECT title_id, type, sales
  FROM titles
  WHERE RAND() < 0.25;