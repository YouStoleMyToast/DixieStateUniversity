SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE ta.au_id = a.au_id
      HAVING COUNT(*) >= 3);