SELECT au_id, au_fname, au_lname, state
  FROM authors
  WHERE state IN
    (SELECT state
      FROM authors
      WHERE au_id = 'A04');