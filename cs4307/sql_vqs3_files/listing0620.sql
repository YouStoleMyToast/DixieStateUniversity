SELECT
    type,
    COUNT(price) AS "COUNT(price)"
  FROM titles
  GROUP BY type
  HAVING AVG(price * sales) > 1000000;