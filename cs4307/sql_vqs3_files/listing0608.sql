SELECT
    COUNT(price)
      AS "COUNT(price)",
    SUM(price)
      AS "SUM(price)"
  FROM titles;

SELECT
    COUNT(price)
      AS "COUNT(price)",
    SUM(DISTINCT price)
      AS "SUM(DISTINCT price)"
  FROM titles;

SELECT
    COUNT(DISTINCT price)
      AS "COUNT(DISTINCT price)",
    SUM(price)
      AS "SUM(price)"
  FROM titles;

SELECT
    COUNT(DISTINCT price)
      AS "COUNT(DISTINCT price)",
    SUM(DISTINCT price)
      AS "SUM(DISTINCT price)"
  FROM titles;