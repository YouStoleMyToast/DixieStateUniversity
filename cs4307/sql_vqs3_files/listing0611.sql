SELECT
    type,
    SUM(sales)   AS "SUM(sales)",
    COUNT(sales) AS "COUNT(sales)",
    COUNT(*)     AS "COUNT(*)",
    SUM(sales)/COUNT(sales)
      AS "SUM/COUNT(sales)",
    SUM(sales)/COUNT(*)
      AS "SUM/COUNT(*)",
    AVG(sales)   AS "AVG(sales)"
  FROM titles
  GROUP BY type;