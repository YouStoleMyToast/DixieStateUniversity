SELECT title_id, title_name
  FROM titles
  WHERE type <> 'biography'
    AND price < ALL
    (SELECT price 
      FROM titles
      WHERE type = 'biography'
        AND price IS NOT NULL);