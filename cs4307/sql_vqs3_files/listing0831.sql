SELECT type, title_id, price
  FROM titles t1
  WHERE price >
    (SELECT AVG(t2.price)
      FROM titles t2
      WHERE t1.type = t2.type)
  ORDER BY type ASC, title_id ASC;