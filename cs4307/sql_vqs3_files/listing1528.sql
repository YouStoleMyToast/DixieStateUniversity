SELECT emp_id, sales
  FROM empsales
  WHERE (
    sales >= (
      SELECT sales
        FROM empsales
        ORDER BY sales DESC
        LIMIT 1 OFFSET 2)
  ) IS NOT FALSE
  ORDER BY sales DESC;