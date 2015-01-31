SELECT TOP 3 WITH TIES emp_id, sales
  FROM empsales
  ORDER BY sales DESC;