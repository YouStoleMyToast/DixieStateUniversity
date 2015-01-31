SELECT AVG(sales) AS median
  FROM
    (SELECT e1.sales
       FROM empsales e1, empsales e2
       GROUP BY e1.sales
       HAVING
         SUM(CASE WHEN e1.sales = e2.sales THEN 1 ELSE 0 END) >=
             ABS(SUM(SIGN(e1.sales - e2.sales)))) t1;