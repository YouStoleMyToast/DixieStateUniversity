SELECT
    'author' AS "Type",
    au_fname || ' ' || au_lname AS "Name"
  FROM authors
  WHERE state = 'NY'
UNION
SELECT
    'publisher',
    pub_name
  FROM publishers
  WHERE state = 'NY'
UNION
SELECT
    'title',
    title_name
  FROM titles t
  INNER JOIN publishers p
    ON t.pub_id = p.pub_id
  WHERE p.state = 'NY'
  ORDER BY 1 ASC, 2 ASC;