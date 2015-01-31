SELECT emp_id, sales
  FROM empsales
  WHERE sales >= COALESCE(
    (SELECT sales
       FROM empsales
       ORDER BY sales DESC
       LIMIT 1 OFFSET 2),
    (SELECT MIN(sales)
       FROM empsales))
  ORDER BY sales DESC;