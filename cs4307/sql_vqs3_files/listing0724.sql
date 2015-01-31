SELECT
    t.pub_id,
    ta.au_id,
    COUNT(*) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) -
      (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM title_authors ta
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  INNER JOIN publishers p
    ON p.pub_id = t.pub_id
  WHERE t.sales IS NOT NULL
    AND p.country IN ('USA')
  GROUP BY t.pub_id, ta.au_id
  HAVING SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - 
    (r.advance * ta.royalty_share)) > 0
  ORDER BY t.pub_id ASC, ta.au_id ASC;