SELECT
    'author' AS "Type",
    au_fname || ' ' || au_lname AS "Name",
    state
  FROM authors
  WHERE state = 'NY'
UNION
SELECT
    'publisher',
    pub_name,
    state
  FROM publishers
  WHERE state = 'NY'
  ORDER BY 1 ASC, 2 ASC;