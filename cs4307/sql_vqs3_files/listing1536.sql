SELECT title_name, type, price,
    COUNT(*) AS NumDups
  FROM dups
  GROUP BY title_name, type, price
  HAVING COUNT(*) >= 1
  ORDER BY COUNT(*) DESC;