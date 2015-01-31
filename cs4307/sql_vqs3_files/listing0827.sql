SELECT au_id, title_id
  FROM title_authors ta
  WHERE
    (SELECT AVG(sales)
      FROM titles t
      WHERE ta.title_id = t.title_id)
    >
    (SELECT AVG(sales)
      FROM titles)
  ORDER BY au_id ASC, title_id ASC;