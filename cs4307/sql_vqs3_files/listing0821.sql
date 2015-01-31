SELECT t1.title_id, t1.sales,
    (SELECT SUM(t2.sales)
      FROM titles t2
      WHERE t2.title_id <= t1.title_id)
        AS "Running total"
  FROM titles t1;