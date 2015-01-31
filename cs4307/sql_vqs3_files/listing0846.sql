SELECT t1.type
  FROM titles t1
  GROUP BY t1.type
  HAVING MAX(t1.sales) >= ALL
    (SELECT 2.0 * AVG(t2.sales)
      FROM titles t2
      WHERE t1.type = t2.type);