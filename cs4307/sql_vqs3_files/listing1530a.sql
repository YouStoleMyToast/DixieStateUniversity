SELECT e1.emp_id, e1.sales,
    (SELECT COUNT(sales)
       FROM empsales e2
       WHERE e2.sales >= e1.sales)
         AS ranking
  FROM empsales e1;