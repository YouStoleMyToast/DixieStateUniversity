SELECT emp_id, sales
  FROM (
    SELECT
        RANK() OVER
          (ORDER BY sales DESC)
            AS sales_rank,
        emp_id,
        sales
      FROM empsales)
        AS any_name
  WHERE sales_rank <= 3;