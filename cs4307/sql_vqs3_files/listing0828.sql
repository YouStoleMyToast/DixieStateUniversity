SELECT title_id, price
  FROM titles
  WHERE price >
    (SELECT MAX(price)
      FROM titles
      GROUP BY type
      HAVING type = 'biography');