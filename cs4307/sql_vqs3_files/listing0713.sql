SELECT
    t.type,
    COUNT(r.advance)
      AS "COUNT(r.advance)",
    SUM(r.advance)
      AS "SUM(r.advance)"
  FROM royalties r
  INNER JOIN titles t
    ON r.title_id = t.title_id
  WHERE r.advance IS NOT NULL
  GROUP BY t.type
  ORDER BY t.type ASC;