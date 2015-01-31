SELECT title_id,
    (CASE WHEN i=1 THEN '1'
          WHEN i=2 THEN '2'
          WHEN i=3 THEN '3'
    END) AS au_order,
    (CASE WHEN i=1 THEN author1
          WHEN i=2 THEN author2
          WHEN i=3 THEN author3
    END) AS au_id
  FROM au_orders, seq
  WHERE i BETWEEN 1 AND 3
  ORDER BY title_id, i;