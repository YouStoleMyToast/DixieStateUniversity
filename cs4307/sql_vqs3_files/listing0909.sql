SELECT city 
  FROM authors
EXCEPT
SELECT city 
  FROM publishers;