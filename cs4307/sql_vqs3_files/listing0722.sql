SELECT
    t.pub_id,
    COUNT(t.sales) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate) AS "Total royalties",
    SUM(r.advance) AS "Total advances",
    SUM((t.sales * t.price * r.royalty_rate) - r.advance) AS "Total due to authors"
  FROM titles t
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL
  GROUP BY t.pub_id
  ORDER BY t.pub_id ASC;