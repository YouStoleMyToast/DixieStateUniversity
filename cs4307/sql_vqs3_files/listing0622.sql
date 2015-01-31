SELECT
    type,
    SUM(sales) AS "SUM(sales)",
    AVG(price) AS "AVG(price)"
  FROM titles
  WHERE pub_id IN ('P03', 'P04')
  GROUP BY type
  HAVING SUM(sales) > 10000
     AND AVG(price) < 20;