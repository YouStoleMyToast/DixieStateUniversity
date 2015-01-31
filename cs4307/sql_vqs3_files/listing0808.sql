SELECT title_id, price
  FROM titles
  WHERE price = 
    (SELECT MAX(price)
      FROM titles);