# chapter 9

########  Union   ##########
# List the states with an author or publisher
SELECT state FROM authors
UNION
SELECT state FROM publishers;

# List the states with an author or publisher include dups
SELECT state FROM authors
UNION ALL
SELECT state FROM publishers;

# list the authors and publishers
SELECT au_fname || ' ' || au_lname AS "Name"
  FROM authors
UNION
SELECT pub_name
  FROM publishers
  ORDER BY 1 ASC;

########  INTERSECT   ###################
# list the cities with both an author and a publisher

#intersect keyword not supported by mysql
SELECT city 
  FROM authors
INTERSECT
SELECT city 
  FROM publishers;

#slower way
SELECT DISTINCT authors.city
  FROM authors
  INNER JOIN publishers
    ON authors.city = publishers.city;

#faster way
SELECT DISTINCT city
  FROM authors
  WHERE EXISTS (SELECT * FROM publishers WHERE authors.city = publishers.city);



#########   EXCEPT (Difference or Minus)  #################
# List the cities with an author but no publisher

#except keyword not supported by mysql
SELECT city 
  FROM authors
EXCEPT
SELECT city 
  FROM publishers;

#slow
SELECT DISTINCT a.city
  FROM authors a
  LEFT OUTER JOIN publishers p
    ON a.city = p.city
  WHERE p.city IS NULL;

#both below are similar in speed
SELECT DISTINCT city
  FROM authors
  WHERE NOT EXISTS (SELECT * FROM publishers WHERE authors.city = publishers.city);

SELECT DISTINCT city
  FROM authors
  WHERE city NOT IN (SELECT city FROM publishers);




