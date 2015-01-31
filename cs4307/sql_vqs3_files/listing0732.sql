SELECT a.au_id, a.au_fname, a.au_lname,
    tta.title_id, tta.title_name, tta.sales
  FROM authors a
  LEFT OUTER JOIN
  (SELECT ta.au_id, t.title_id,
      t.title_name, t.sales
    FROM title_authors ta
    INNER JOIN titles t
      ON t.title_id = ta.title_id
    WHERE sales > 100000) tta
    ON a.au_id = tta.au_id
  ORDER BY a.au_id ASC, tta.title_id ASC;