SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city = ANY
    (SELECT city
      FROM publishers);