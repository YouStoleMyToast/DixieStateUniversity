SELECT title_id, title_name
  FROM titles
  WHERE type <> 'biography'
    AND price < ANY
      (SELECT price 
        FROM titles
        WHERE type = 'biography');