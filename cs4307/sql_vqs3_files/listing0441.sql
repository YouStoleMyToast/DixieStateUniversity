SELECT title_id, pubdate
  FROM titles
  WHERE pubdate IN
        (DATE '2000-01-01',
         DATE '2001-01-01',
         DATE '2002-01-01');