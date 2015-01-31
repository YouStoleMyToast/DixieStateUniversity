SELECT au_id, city
  FROM authors
  WHERE city IN
    (SELECT city
      FROM publishers);