SELECT
    ta.au_id,
    COUNT(sales) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) -
      (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM title_authors ta
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL
  GROUP BY ta.au_id
  ORDER BY ta.au_id ASC;