SELECT emp_id, sales
  FROM empsales
  ORDER BY sales DESC
  FETCH FIRST 3 ROWS ONLY;