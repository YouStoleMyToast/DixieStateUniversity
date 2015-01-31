SELECT a.au_id, au_fname, au_lname
  FROM authors a
  WHERE 1.0 IN
    (SELECT royalty_share
      FROM title_authors ta
      WHERE ta.au_id = a.au_id);