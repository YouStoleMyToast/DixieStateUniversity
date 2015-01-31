SELECT
    'author' AS "Type",
    COUNT(au_id) AS "Count"
  FROM authors
  WHERE state = 'NY'
UNION
SELECT
    'publisher',
    COUNT(pub_id)
  FROM publishers
  WHERE state = 'NY'
UNION
SELECT
    'title',
    COUNT(title_id)
  FROM titles t
  INNER JOIN publishers p
    ON t.pub_id = p.pub_id
  WHERE p.state = 'NY'
  ORDER BY 1 ASC;