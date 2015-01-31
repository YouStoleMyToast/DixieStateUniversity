SELECT
    COUNT(*)     AS "COUNT(*)"
  FROM titles;

SELECT
    COUNT(price) AS "COUNT(price)",
    SUM(price)   AS "SUM(price)",
    AVG(price)   AS "AVG(price)"
  FROM titles;

SELECT
    COUNT(DISTINCT price)
      AS "COUNT(DISTINCT)",
    SUM(DISTINCT price)
      AS "SUM(DISTINCT)",
    AVG(DISTINCT price)
      AS "AVG(DISTINCT)"
  FROM titles;