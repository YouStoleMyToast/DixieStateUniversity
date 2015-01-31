SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE NOT EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE a.au_id = ta.au_id);