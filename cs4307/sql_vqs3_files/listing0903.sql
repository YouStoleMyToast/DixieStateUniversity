SELECT au_fname || ' ' || au_lname AS "Name"
  FROM authors
UNION
SELECT pub_name
  FROM publishers
  ORDER BY 1 ASC;