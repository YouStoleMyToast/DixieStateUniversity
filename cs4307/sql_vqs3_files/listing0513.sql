SELECT SUBSTRING(au_fname FROM 1 FOR 1)
       || '. '
       || au_lname
         AS "Author name",
       state
  FROM authors
  WHERE state IN ('NY', 'CO');