SELECT
    au_fname,
    POSITION('e' IN au_fname) AS "Pos e",
    au_lname,
    POSITION('ma' IN au_lname) AS "Pos ma"
  FROM authors;