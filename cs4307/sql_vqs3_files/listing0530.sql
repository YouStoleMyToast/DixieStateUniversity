SELECT
    title_id,
    type,
    price,
    CASE type
      WHEN 'history'
        THEN price * 1.10
      WHEN 'psychology'
        THEN price * 1.20
      ELSE price
    END
      AS "New price"
  FROM titles
  ORDER BY type ASC, title_id ASC;