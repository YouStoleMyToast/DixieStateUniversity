SELECT title_id, pubdate
  FROM titles
  WHERE pubdate BETWEEN DATE '2000-01-01'
                AND     DATE '2000-12-31';