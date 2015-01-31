#  list the biography publishers 
SELECT DISTINCT pub_name
  FROM publishers p
  INNER JOIN titles t
    ON p.pub_id = t.pub_id
  WHERE t.type = 'biography';
SELECT pub_name
  FROM publishers
  WHERE pub_id IN
    (SELECT pub_id
      FROM titles
      WHERE type = 'biography');

# list authors who live in same city as a publisher
SELECT au_id, city
  FROM authors
  WHERE city IN
    (SELECT city FROM publishers);
SELECT DISTINCT a.au_id, a.city
  FROM authors a
  INNER JOIN publishers p
    ON a.city = p.city;

# list authors who havent written a book
SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE au_id NOT IN
     (SELECT au_id FROM title_authors);
SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE NOT EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE a.au_id = ta.au_id);
SELECT a.au_id, a.au_fname, a.au_lname
  FROM authors a
  LEFT OUTER JOIN title_authors ta
    ON a.au_id = ta.au_id
  WHERE ta.au_id IS NULL;

# list authors who live in same state as A04
SELECT au_id, au_fname, au_lname, state
  FROM authors
  WHERE state IN
    (SELECT state
      FROM authors
      WHERE au_id = 'A04');
SELECT a1.au_id, a1.au_fname,
    a1.au_lname, a1.state
  FROM authors a1
  INNER JOIN authors a2
    ON a1.state = a2.state
  WHERE a2.au_id = 'A04';


# list books whose price = highest price
SELECT title_id, price
  FROM titles
  WHERE price = 
    (SELECT MAX(price)
      FROM titles);

# list books with sales >= average sales of books in its category
# (correlated subquery)  inner query cannt be answered without outer query
SELECT
    candidate.title_id,
    candidate.type,
    candidate.sales
  FROM titles candidate
  WHERE sales >=
    (SELECT AVG(sales)
      FROM titles average
      WHERE average.type = candidate.type);

# list all the authers of each book (one row)
#   (Cross tablulation)
SELECT title_id,
    (SELECT au_id
      FROM title_authors ta
      WHERE au_order = 1
        AND title_id = t.title_id)
        AS "Author 1",
    (SELECT au_id
      FROM title_authors ta
      WHERE au_order = 2
        AND title_id = t.title_id)
        AS "Author 2",
    (SELECT au_id
      FROM title_authors ta
      WHERE au_order = 3
        AND title_id = t.title_id)
        AS "Author 3"
  FROM titles t;

# list the # of books each author wrote
SELECT au_id,
    (SELECT COUNT(*)
      FROM title_authors ta
      WHERE ta.au_id = a.au_id)
        AS "Num books"
  FROM authors a
  ORDER BY au_id ASC;

# list the authors and the latest publish date
SELECT au_id, 
    (SELECT MAX(pubdate)
      FROM titles t
      INNER JOIN title_authors ta
        ON ta.title_id = t.title_id
      WHERE ta.au_id = a.au_id)
        AS "Latest pub date"
  FROM authors a;

# compute running subtotal of book sales
SELECT t1.title_id, t1.sales,
    (SELECT SUM(t2.sales)
      FROM titles t2
      WHERE t2.title_id <= t1.title_id)
        AS "Running total"
  FROM titles t1;

# which author wrote the greatest number of books
SELECT MAX(ta.count_titles) AS "Max titles"
  FROM (SELECT COUNT(*) AS count_titles
         FROM title_authors
         GROUP BY au_id) ta;

# list the books with above average sales
SELECT title_id, sales
  FROM titles
  WHERE sales >
    (SELECT AVG(sales)
      FROM titles);

# list the books priced higher than the highest priced biography
SELECT title_id, price
  FROM titles
  WHERE price >
    (SELECT MAX(price)
      FROM titles
      GROUP BY type
      HAVING type = 'biography');

# list the books that have a higher price than the average of its type
SELECT type, title_id, price
  FROM titles t1
  WHERE price >
    (SELECT AVG(t2.price)
      FROM titles t2
      WHERE t1.type = t2.type)
  ORDER BY type ASC, title_id ASC;

# list the names of the publishers that have a published biography
SELECT pub_name
  FROM publishers
  WHERE pub_id IN
    (SELECT pub_id
      FROM titles
      WHERE type = 'biography');

# list the names of publishers that havent published a biography
SELECT pub_name
  FROM publishers
  WHERE pub_id NOT IN
    (SELECT pub_id
      FROM titles
      WHERE type = 'biography');

# list the authors who have participated in writting a biography
SELECT au_id, au_fname, au_lname
  FROM authors
  WHERE au_id IN
    (SELECT au_id
      FROM title_authors
      WHERE title_id IN
        (SELECT title_id
          FROM titles
          WHERE type = 'biography'));

# list the types of books common to more than one publisher
SELECT DISTINCT t1.type
  FROM titles t1
  WHERE t1.type IN
    (SELECT t2.type
      FROM titles t2
      WHERE t1.pub_id <> t2.pub_id);
SELECT DISTINCT t1.type
  FROM titles t1
  INNER JOIN titles t2 ON t1.type=t2.type and t1.pub_id<>t2.pub_id;

# list the authors who live in a city in which there are NO publishers
SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city <> ALL
    (SELECT city
      FROM publishers);

# list the non-biographies that are cheaper than all the biographies
SELECT title_id, title_name
  FROM titles
  WHERE type <> 'biography'
    AND price < ALL
    (SELECT price 
      FROM titles
      WHERE type = 'biography'
        AND price IS NOT NULL);
# list the books that outsold all the books A06 wrote
SELECT title_id, title_name
  FROM titles
  WHERE sales > ALL
    (SELECT sales
      FROM title_authors ta
      INNER JOIN titles t
        ON t.title_id = ta.title_id
      WHERE ta.au_id = 'A06'
        AND sales IS NOT NULL);

# list the types of books for which the highest sales figure is double
# average sales for that type
SELECT t1.type
  FROM titles t1
  GROUP BY t1.type
  HAVING MAX(t1.sales) >= ALL
    (SELECT 2.0 * AVG(t2.sales)
      FROM titles t2
      WHERE t1.type = t2.type);

# list the authors who live in a publishers city
SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city = ANY
    (SELECT city
      FROM publishers);
SELECT au_id, au_lname, au_fname, city
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);

# list the non-biographies that are cheaper than any biography
SELECT title_id, title_name
  FROM titles
  WHERE type <> 'biography'
    AND price < ANY
      (SELECT price 
        FROM titles
        WHERE type = 'biography');

============================================================================
# list the books that outsold at least one of the books that A06 wrote
SELECT title_id, title_name
  FROM titles
  WHERE sales > ANY
    (SELECT sales
      FROM title_authors ta
      INNER JOIN titles t
        ON t.title_id = ta.title_id
      WHERE ta.au_id = 'A06');

# list the cities in which there are both an author and publisher
SELECT DISTINCT city
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);

# author cities minus publisher cities
SELECT DISTINCT city
  FROM authors a
  WHERE NOT EXISTS
    (SELECT *
      FROM publishers p
      WHERE p.city = a.city);

# list the authors who wrote 3 or more books
SELECT au_id, au_fname, au_lname
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE ta.au_id = a.au_id
      HAVING COUNT(*) >= 3);

# list the authors who wrote at least one book
SELECT DISTINCT a.au_id
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id;
SELECT DISTINCT a.au_id
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id;
SELECT au_id
  FROM authors a
  WHERE au_id IN
    (SELECT au_id
      FROM title_authors);
SELECT au_id
  FROM authors a
  WHERE au_id = ANY
    (SELECT au_id
      FROM title_authors);
SELECT au_id
  FROM authors a
  WHERE EXISTS
    (SELECT *
      FROM title_authors ta
      WHERE a.au_id = ta.au_id);
SELECT au_id
  FROM authors a
  WHERE 0 <
    (SELECT COUNT(*)
      FROM title_authors ta
      WHERE a.au_id = ta.au_id);






