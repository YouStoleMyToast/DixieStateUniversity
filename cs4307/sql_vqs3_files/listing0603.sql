SELECT SUM(advance) AS "Total advances"
  FROM royalties;

SELECT SUM(sales)
         AS "Total sales (2000 books)"
  FROM titles
  WHERE pubdate
    BETWEEN DATE '2000-01-01'
        AND DATE '2000-12-31';

SELECT
    SUM(price) AS "Total price",
    SUM(sales) AS "Total sales",
    SUM(price * sales) AS "Total revenue"
  FROM titles;