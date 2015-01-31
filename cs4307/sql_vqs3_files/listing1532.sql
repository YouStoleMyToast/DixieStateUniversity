SELECT AVG(sales) AS TrimmedMean
  FROM titles t1
  WHERE
    (SELECT COUNT(*)
       FROM titles t2
       WHERE t2.sales <= t1.sales) >=
         (SELECT 0.25 * COUNT(*)
            FROM titles)
    AND
    (SELECT COUNT(*)
       FROM titles t3
       WHERE t3.sales >= t1.sales) >=
         (SELECT 0.25 * COUNT(*) 
            FROM titles);