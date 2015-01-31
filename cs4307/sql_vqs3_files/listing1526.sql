SELECT emp_id, sales
  FROM empsales
  ORDER BY sales DESC
  LIMIT 3 OFFSET 4;