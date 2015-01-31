SELECT
    SUM(t.sales * t.price * r.royalty_rate) AS "Total royalties",
    SUM(r.advance) AS "Total advances",
    SUM((t.sales * t.price * r.royalty_rate) - r.advance) AS "Total due to authors"
  FROM titles t
  INNER JOIN royalties r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL;