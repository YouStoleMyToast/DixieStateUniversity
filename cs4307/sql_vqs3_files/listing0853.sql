SELECT DISTINCT city
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);