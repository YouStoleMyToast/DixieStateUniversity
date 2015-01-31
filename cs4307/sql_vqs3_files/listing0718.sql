SELECT
    a.au_fname,
    a.au_lname,
    t.title_name,
    p.pub_name
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  INNER JOIN publishers p
    ON p.pub_id = t.pub_id
  ORDER BY a.au_lname ASC, a.au_fname ASC,
    t.title_name ASC;