SELECT ta.au_id, ta.title_id
  FROM titles t
  INNER JOIN title_authors ta
    ON ta.title_id = t.title_id
  WHERE sales >
    (SELECT AVG(sales)
      FROM titles)
  ORDER BY ta.au_id ASC, ta.title_id ASC;