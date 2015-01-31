SELECT au_id, au_lname, au_fname, city
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);