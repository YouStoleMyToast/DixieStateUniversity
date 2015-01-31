SELECT pub_id
  FROM publishers
  WHERE EXISTS
    (SELECT COUNT(*)
      FROM titles
      WHERE pub_id = 'XXX');