SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM title_authors ta
      INNER JOIN titles t
        ON t.title_id = ta.title_id
      WHERE ta.au_id = a.au_id
        AND t.type = 'children')
  AND EXISTS
    (SELECT *
      FROM title_authors ta
      INNER JOIN titles t
        ON t.title_id = ta.title_id
      WHERE ta.au_id = a.au_id
        AND t.type = 'psychology');