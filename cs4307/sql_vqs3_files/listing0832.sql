SELECT type, title_id, sales
  FROM titles t1
  WHERE sales <
    (SELECT MAX(sales)
      FROM titles t2
      WHERE t1.type = t2.type
        AND sales IS NOT NULL)
  ORDER BY type ASC, title_id ASC;