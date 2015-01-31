SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE NOT EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE ta.au_id = a.au_id);