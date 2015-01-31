SELECT a.au_id, a.city, p.pub_id
  FROM authors a
  INNER JOIN publishers p
    ON a.city = p.city;