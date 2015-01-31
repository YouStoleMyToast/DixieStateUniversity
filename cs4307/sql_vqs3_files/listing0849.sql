SELECT title_id, title_name
  FROM titles
  WHERE sales > ANY
    (SELECT sales
      FROM title_authors ta
      INNER JOIN titles t
        ON t.title_id = ta.title_id
      WHERE ta.au_id = 'A06');