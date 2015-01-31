SELECT title_name, type, price
  FROM dups
  GROUP BY title_name, type, price
  HAVING COUNT(*) > 1;