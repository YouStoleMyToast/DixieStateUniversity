SELECT au_fname, au_lname, state
  FROM authors
  WHERE au_lname >= 'H'
    AND au_lname <= 'Zz'
    AND state <> 'CA';