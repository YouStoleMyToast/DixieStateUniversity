SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE au_id NOT IN
     (SELECT au_id FROM title_authors);