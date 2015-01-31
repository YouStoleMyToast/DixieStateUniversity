SELECT emp_id, sales
  FROM (
    SELECT *
      FROM empsales
      ORDER BY sales DESC)
  WHERE ROWNUM <= 3;