SELECT au_fname, au_lname, phone
  FROM authors
  WHERE SUBSTRING(phone FROM 1 FOR 3)='415';