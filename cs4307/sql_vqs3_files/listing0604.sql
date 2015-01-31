SELECT AVG(price * 2) AS "AVG(price * 2)"
  FROM titles;

SELECT AVG(sales) AS "AVG(sales)",
       SUM(sales) AS "SUM(sales)"
  FROM titles
  WHERE type = 'business';

SELECT title_id, sales
  FROM titles
  WHERE sales >
        (SELECT AVG(sales) FROM titles)
  ORDER BY sales DESC;