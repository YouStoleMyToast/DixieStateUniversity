SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM title_authors ta
  INNER JOIN authors a
    ON ta.au_id = a.au_id
  WHERE title_id IN
    (SELECT title_id
      FROM titles
      WHERE pub_id = 'P03');