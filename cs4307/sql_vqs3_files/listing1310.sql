SELECT DISTINCT an.au_fname, an.au_lname
  FROM au_names an
  INNER JOIN title_authors ta
    ON an.au_id = ta.au_id
  WHERE ta.au_order > 1;