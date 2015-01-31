SELECT MAX(au_lname) AS "Max last name"
  FROM authors;

SELECT
    MIN(price) AS "Min price",
    MAX(price) AS "Max price",
    MAX(price) - MIN(price) AS "Range"
  FROM titles;

SELECT MAX(price * sales)
         AS "Max history revenue"
  FROM titles
  WHERE type = 'history';