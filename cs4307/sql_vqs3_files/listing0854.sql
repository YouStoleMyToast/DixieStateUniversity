SELECT DISTINCT city
  FROM authors a
  WHERE NOT EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);