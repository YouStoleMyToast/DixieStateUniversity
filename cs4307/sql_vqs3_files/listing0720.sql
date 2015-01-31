SELECT
    ta.au_id,
    t.title_id,
    t.pub_id,
    t.sales * t.price * r.royalty_rate * ta.royalty_share AS "Royalty share",
    r.advance * ta.royalty_share AS "Advance share",
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) -
      (r.advance * ta.royalty_share) AS "Due to author"
  FROM title_authors ta
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL
  ORDER BY ta.au_id ASC, t.title_id ASC;