SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a
  INNER JOIN publishers p
    ON a.city = p.city;