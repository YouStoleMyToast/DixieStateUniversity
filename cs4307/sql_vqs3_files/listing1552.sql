-- Works in SQL Server 2000 and later.
SELECT
  (
    (SELECT MAX(sales) FROM
       (SELECT TOP 50 PERCENT sales
          FROM empsales
          ORDER BY sales ASC) AS t1)
     +
     (SELECT MIN(sales) FROM
       (SELECT TOP 50 PERCENT sales
          FROM empsales
          ORDER BY sales DESC) AS t2)
  )/2 AS median;

-- Works in SQL Server 2005 and later.
-- Works in DB2.
SELECT AVG(sales) AS median
  FROM
    (SELECT
        sales,
        ROW_NUMBER() OVER (ORDER BY sales) AS rownum,
        COUNT(*) OVER () AS cnt
      FROM empsales) t1
  WHERE rownum IN ((cnt+1)/2, (cnt+2)/2);