SELECT title_id,
    price,
    (SELECT AVG(price) FROM titles)
      AS "AVG(price)",
    price - (SELECT AVG(price) FROM titles)
      AS "Difference"
  FROM titles
  WHERE type='biography';