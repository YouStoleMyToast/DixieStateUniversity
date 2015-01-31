SELECT title_name,
       CHARACTER_LENGTH(title_name) AS "Len"
  FROM titles
  WHERE CHARACTER_LENGTH(title_name) < 30
  ORDER BY CHARACTER_LENGTH(title_name) ASC;