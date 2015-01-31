SELECT AVG(sales) AS TrimmedMean
  FROM titles t1
  WHERE
    (SELECT COUNT(*)
       FROM titles t2
       WHERE t2.sales <= t1.sales) > 3
    AND
    (SELECT COUNT(*)
       FROM titles t3
       WHERE t3.sales >= t1.sales) > 3;