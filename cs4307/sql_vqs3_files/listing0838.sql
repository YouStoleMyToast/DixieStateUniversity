SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE state = 'CA'
    AND au_id IN
      (SELECT au_id
        FROM title_authors
        WHERE royalty_share < 0.5
          AND au_order > 1);