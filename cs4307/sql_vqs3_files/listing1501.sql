SELECT 
    t1.title_id,
    SUM(t2.sales) AS RunSum,
    AVG(t2.sales) AS RunAvg,
    COUNT(t2.sales) AS RunCount
  FROM titles t1, titles t2
  WHERE t1.title_id >= t2.title_id
  GROUP BY t1.title_id
  ORDER BY t1.title_id;