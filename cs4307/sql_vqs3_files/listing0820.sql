SELECT au_id, 
    (SELECT MAX(pubdate)
      FROM titles t
      INNER JOIN title_authors ta
        ON ta.title_id = t.title_id
      WHERE ta.au_id = a.au_id)
        AS "Latest pub date"
  FROM authors a;