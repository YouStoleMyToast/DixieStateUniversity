SELECT
    a.au_id,
    a.au_fname,
    a.au_lname,
    t.title_name,
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) -
      (r.advance * ta.royalty_share) AS "Due to author"
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL
    AND (t.sales * t.price * r.royalty_rate * ta.royalty_share) -
      (r.advance * ta.royalty_share) > 0
  ORDER BY a.au_id ASC, t.title_id ASC;