SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE au_id IN
    (SELECT au_id
      FROM title_authors
      WHERE royalty_share = 1.0);