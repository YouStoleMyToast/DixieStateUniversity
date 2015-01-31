SELECT price, AVG(sales) AS "AVG(sales)"
  FROM titles
  WHERE price IS NOT NULL
  GROUP BY price
  ORDER BY price ASC;