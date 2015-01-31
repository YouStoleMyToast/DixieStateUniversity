SELECT au_fname AS "First name",
       au_lname AS "Last name",
       state
  FROM authors
  ORDER BY state        ASC,
           "Last name"  ASC,
           "First name" ASC;