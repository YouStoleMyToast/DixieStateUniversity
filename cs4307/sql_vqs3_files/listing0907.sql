SELECT title_id, type, price,
    price * 1.10 AS "New price"
  FROM titles
  WHERE type = 'history'
UNION
SELECT title_id, type, price, price * 1.20
  FROM titles
  WHERE type = 'psychology'
UNION
SELECT title_id, type, price, price
  FROM titles
  WHERE type NOT IN ('psychology','history')
  ORDER BY type ASC, title_id ASC;