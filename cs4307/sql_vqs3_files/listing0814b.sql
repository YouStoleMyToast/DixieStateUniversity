SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE 1.0 IN
    (SELECT royalty_share
      FROM title_authors
      WHERE title_authors.au_id =
            authors.au_id);