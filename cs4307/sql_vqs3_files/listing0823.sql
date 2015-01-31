SELECT au_id, au_fname, au_lname, state
  FROM authors
  WHERE state =
    (SELECT state
      FROM publishers
      WHERE pub_name = 'Tenterhooks Press');