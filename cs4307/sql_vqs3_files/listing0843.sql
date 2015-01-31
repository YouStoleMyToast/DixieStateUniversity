SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city <> ALL
    (SELECT city
      FROM publishers);