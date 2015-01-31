SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE au_id IN
    (SELECT au_id
      FROM title_authors
      WHERE title_id IN
        (SELECT title_id
          FROM titles
          WHERE type = 'biography'));