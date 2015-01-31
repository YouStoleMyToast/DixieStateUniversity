SELECT
    a.au_id,
    a.au_fname,
    a.au_lname,
    ta.title_id
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  ORDER BY a.au_id ASC, ta.title_id ASC;