-- Works in Oracle 9i and later.
SELECT
    percentile_cont(0.5) WITHIN GROUP (ORDER BY sales) AS median
  FROM empsales;

-- Works in Oracle 10g and later.
SELECT median(sales) AS median
  FROM empsales;