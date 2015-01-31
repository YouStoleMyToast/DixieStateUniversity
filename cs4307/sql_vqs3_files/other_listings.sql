-- Page 10
SELECT SERVERPROPERTY('ProductVersion');

SELECT @@VERSION;

-- Page 17
SELECT banner FROM v$version;

-- Page 20
SELECT service_level FROM SYSIBMADM.ENV_INST_INFO;

-- Page 27
SELECT VERSION();

-- Page 30
SELECT VERSION();

-- Page 62
SELECT au_fname, au_lname
  FROM authors
  WHERE state = 'NY'
  ORDER BY au_lname;

-- Page 92
SELECT au_fname AS "First name",
       au_lname AS "Last name",
       city     AS "City",
       state,
       zip      AS "Postal code"
  FROM authors;

-- Page 123
SELECT au_fname, au_lname, state
  FROM authors
  WHERE state <> 'NY'
    AND state <> 'NJ'
    AND state <> 'CA';

-- Page 126
SELECT pub_id, city, state, country
  FROM publishers
  WHERE country <> 'Canada';

-- Page 129
SELECT 2 + 3
  FROM DUAL;

SELECT 2 + 3
  FROM SYSIBM.SYSDUMMY1;

-- Page 171
SELECT title_id --Illegal
  FROM titles
  WHERE sales = MAX(sales);

SELECT title_id, MAX(sales)
  FROM titles; --Illegal

SELECT type, SUM(sales)
  FROM titles
  GROUP BY type; --Legal

SELECT MIN(sales), MAX(sales)
  FROM titles; --Legal

SELECT SUM(AVG(sales))
  FROM titles; --Illegal

SELECT title_id, price --Legal
  FROM titles
  WHERE sales =
    (SELECT MAX(sales) FROM titles);

SELECT AVG(MAX(sales))
  FROM titles
  GROUP BY type; --Legal in Oracle

SELECT AVG(s.max_sales)
  FROM (SELECT MAX(sales) AS max_sales
          FROM titles
          GROUP BY type) s;

-- Page 176
SELECT AVG(COALESCE(sales,0)) AS AvgSales
  FROM titles
  WHERE type = 'biography';

-- Page 177
SELECT price, COUNT(*) AS frequency
  FROM titles
  GROUP BY price
  HAVING COUNT(*) >= ALL(SELECT COUNT(*) FROM titles GROUP BY price);

-- Page 181
SELECT SUM(price)
  FROM (SELECT DISTINCT price
          FROM titles);

-- Page 192
SELECT pub_id, SUM(sales) --Faster
  FROM titles
  WHERE pub_id IN ('P03', 'P04')
  GROUP BY pub_id
  HAVING SUM(sales) > 10000;

SELECT pub_id, SUM(sales) --Slower
  FROM titles
  GROUP BY pub_id
  HAVING SUM(sales) > 10000
  AND pub_id IN ('P03', 'P04');

-- Page 195
SELECT au_fname, au_lname
  FROM authors;

SELECT authors.au_fname, authors.au_lname
  FROM authors;

SELECT au_id, authors.city
  FROM authors, publishers
  WHERE authors.city = publishers.city;

-- Page 197
SELECT a.au_fname, a.au_lname, a.city
  FROM authors a, publishers p
  WHERE a.city = p.city;

-- Page 203
SELECT au_fname, au_lname, city
  FROM authors
  INNER JOIN publishers
  USING (city);

-- Page 205
SELECT au_id, pub_id, a.state AS "au_state", p.state AS "pub_state"
  FROM authors a, publishers p;

SELECT *
  FROM authors
  CROSS JOIN publishers;

SELECT *
  FROM authors, publishers;

SELECT authors.*, p.pub_id
  FROM authors
  CROSS JOIN publishers p;

SELECT authors.*, p.pub_id
  FROM authors, publishers p;

-- Page 207
SELECT t.title_id, t.pub_id, p.pub_name
  FROM publishers p, titles t
  WHERE p.pub_id = t.pub_id;

SELECT t.title_id, t.pub_id, p.pub_name, r.advance
  FROM publishers p, titles t, royalties r
  WHERE p.pub_id = t.pub_id
    AND t.title_id = r.title_id
    AND r.advance < 20000;

-- Page 208
SELECT t.title_id, t.pub_id, p.pub_name
  FROM publishers p
  INNER JOIN titles t
    ON p.pub_id = t.pub_id;

SELECT t.title_id, t.pub_id, p.pub_name, r.advance
  FROM publishers p
  INNER JOIN titles t
    ON p.pub_id = t.pub_id
  INNER JOIN royalties r
    ON t.title_id = r.title_id
  WHERE r.advance < 20000;

SELECT title_id, pub_id, pub_name
  FROM publishers
  INNER JOIN titles
    USING (pub_id);

SELECT title_id, pub_id, pub_name, advance
  FROM publishers
  INNER JOIN titles
    USING (pub_id)
  INNER JOIN royalties
    USING (title_id)
  WHERE advance < 20000;

-- Page 209
SELECT t.title_id, t.pub_id, p.pub_name
  FROM publishers p
  NATURAL JOIN titles t;

SELECT t.title_id, t.pub_id, p.pub_name, r.advance
  FROM publishers p
  NATURAL JOIN titles t
  NATURAL JOIN royalties r
  WHERE r.advance < 20000;

-- Page 211
SELECT a.au_id, a.au_fname, a.au_lname, ta.title_id
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id
  ORDER BY a.au_id ASC, ta.title_id ASC;

-- Page 212
SELECT t.title_id, t.title_name, t.pub_id, p.pub_name
  FROM titles t, publishers p
  WHERE p.pub_id = t.pub_id
  ORDER BY t.title_name ASC;

-- Page 213
SELECT a.au_id, a.au_fname, a.au_lname, a.city, a.state
  FROM authors a
  NATURAL JOIN publishers p
  ORDER BY a.au_id ASC;

SELECT a.au_id, a.au_fname, a.au_lname, a.city, a.state
  FROM authors a, publishers p
  WHERE a.city = p.city
   AND a.state = p.state
  ORDER BY a.au_id ASC;

-- Page 214
SELECT t.title_id, t.title_name, p.state, p.country
  FROM titles t, publishers p
  WHERE t.pub_id = p.pub_id
    AND (p.state = 'CA' OR p.country NOT IN ('USA', 'Canada', 'Mexico'))
  ORDER BY t.title_id ASC;

-- Page 215
SELECT a.au_id, COUNT(ta.title_id) AS "Num books"
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id
  GROUP BY a.au_id
  ORDER BY a.au_id ASC;

-- Page 216
SELECT t.title_id, t.title_name, r.advance
  FROM royalties r, titles t
  WHERE r.title_id = t.title_id
    AND t.type = 'biography'
    AND r.advance IS NOT NULL
  ORDER BY r.advance DESC;

-- Page 217
SELECT t.type,
    COUNT(r.advance) AS "COUNT(r.advance)",
    SUM(r.advance) AS "SUM(r.advance)"
  FROM royalties r, titles t
  WHERE r.title_id = t.title_id
    AND r.advance IS NOT NULL
  GROUP BY t.type
  ORDER BY t.type ASC;

-- Page 218
SELECT t.type, t.pub_id,
    COUNT(r.advance) AS "COUNT(r.advance)",
    SUM(r.advance) AS "SUM(r.advance)"
  FROM royalties r, titles t
  WHERE r.title_id = t.title_id
    AND r.advance IS NOT NULL
  GROUP BY t.type, t.pub_id
  ORDER BY t.type ASC, t.pub_id ASC;

-- Page 219
SELECT ta.title_id,
    COUNT(ta.au_id) AS "Num authors"
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id
  GROUP BY ta.title_id
  HAVING COUNT(ta.au_id) > 1
  ORDER BY ta.title_id ASC;

-- Page 220
SELECT t.title_id, t.title_name, r.advance,
    t.price * t.sales AS "Revenue"
  FROM titles t, royalties r
  WHERE t.price * t.sales > r.advance * 10
    AND t.title_id = r.title_id
  ORDER BY t.price * t.sales DESC;

-- Page 222
SELECT a.au_fname, a.au_lname, t.title_name
  FROM authors a, title_authors ta, titles t
  WHERE a.au_id = ta.au_id
    AND t.title_id = ta.title_id
  ORDER BY a.au_lname ASC, a.au_fname ASC, t.title_name ASC;

SELECT a.au_fname, a.au_lname, t.title_name
  FROM titles AS t
  INNER JOIN (authors AS a
    INNER JOIN title_authors AS ta
      ON a.au_id = ta.au_id)
    ON t.title_id = ta.title_id
ORDER BY a.au_lname ASC, a.au_fname ASC, t.title_name ASC;

-- Page 224
SELECT a.au_fname, a.au_lname, t.title_name, p.pub_name
  FROM authors a, title_authors ta, titles t, publishers p
  WHERE a.au_id = ta.au_id
    AND t.title_id = ta.title_id
    AND p.pub_id = t.pub_id
  ORDER BY a.au_lname ASC, a.au_fname ASC, t.title_name ASC;

SELECT a.au_fname, a.au_lname, t.title_name, p.pub_name
  FROM (publishers AS p
    INNER JOIN titles AS t
      ON p.pub_id = t.pub_id)
  INNER JOIN (authors AS a
    INNER JOIN title_authors AS ta
      ON a.au_id = ta.au_id)
    ON t.title_id = ta.title_id
  ORDER BY a.au_lname ASC, a.au_fname ASC, t.title_name ASC;

-- Page 225
SELECT
    SUM(t.sales * t.price * r.royalty_rate) AS "Total royalties",
    SUM(r.advance) AS "Total advances",
    SUM((t.sales * t.price * r.royalty_rate) - r.advance) AS "Total due to authors"
  FROM titles t, royalties r
  WHERE r.title_id = t.title_id
    AND t.sales IS NOT NULL;

-- Page 226
SELECT ta.au_id, t.title_id, t.pub_id,
    t.sales * t.price * r.royalty_rate * ta.royalty_share AS "Royalty share",
    r.advance * ta.royalty_share AS "Advance share",
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) AS "Due to author"
  FROM title_authors ta, titles t, royalties r
  WHERE t.title_id = ta.title_id
    AND r.title_id = t.title_id
    AND t.sales IS NOT NULL
  ORDER BY ta.au_id ASC, t.title_id ASC;

SELECT ta.au_id, t.title_id, t.pub_id,
    t.sales * t.price * r.royalty_rate * ta.royalty_share AS "Royalty share",
    r.advance * ta.royalty_share AS "Advance share",
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) AS "Due to author"
  FROM (titles AS t
    INNER JOIN royalties AS r
      ON t.title_id = r.title_id)
  INNER JOIN title_authors AS ta
    ON t.title_id = ta.title_id
  WHERE t.sales IS NOT NULL
  ORDER BY ta.au_id ASC, t.title_id ASC;

-- Page 228
SELECT a.au_id, a.au_fname, a.au_lname, t.title_name,
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) AS "Due to author"
  FROM authors a, title_authors ta, titles t, royalties r
  WHERE a.au_id = ta.au_id
    AND t.title_id = ta.title_id
    AND r.title_id = t.title_id
    AND t.sales IS NOT NULL
    AND (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) > 0
  ORDER BY a.au_id ASC, t.title_id ASC;

-- Page 229
SELECT a.au_id, a.au_fname, a.au_lname, t.title_name,
    (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) AS "Due to author"
  FROM (titles AS t
    INNER JOIN royalties AS r
      ON t.title_id = r.title_id)
  INNER JOIN (authors AS a
    INNER JOIN title_authors AS ta
      ON a.au_id = ta.au_id)
    ON t.title_id = ta.title_id
  WHERE t.sales IS NOT NULL
    AND (t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share) > 0
  ORDER BY a.au_id ASC, t.title_id ASC;

-- Page 230
SELECT t.pub_id,
    COUNT(t.sales) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate) AS "Total royalties",
    SUM(r.advance) AS "Total advances",
    SUM((t.sales * t.price * r.royalty_rate) - r.advance) AS "Total due to authors"
  FROM titles t, royalties r
  WHERE r.title_id = t.title_id
    AND t.sales IS NOT NULL
  GROUP BY t.pub_id
  ORDER BY t.pub_id ASC;

-- Page 232
SELECT ta.au_id,
    COUNT(sales) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM title_authors ta, titles t, royalties r
  WHERE t.title_id = ta.title_id
    AND r.title_id = t.title_id
    AND t.sales IS NOT NULL
  GROUP BY ta.au_id
  ORDER BY ta.au_id ASC;

SELECT ta.au_id,
    COUNT(sales) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM (title_authors AS ta
    INNER JOIN titles AS t
      ON t.title_id = ta.title_id)
  INNER JOIN royalties AS r
    ON r.title_id = t.title_id
  WHERE t.sales IS NOT NULL
  GROUP BY ta.au_id
  ORDER BY ta.au_id ASC;

-- Page 234
SELECT t.pub_id, ta.au_id,
    COUNT(*) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM title_authors ta, titles t, royalties r, publishers p
  WHERE t.title_id = ta.title_id
    AND r.title_id = t.title_id
    AND p.pub_id = t.pub_id
    AND t.sales IS NOT NULL
    AND p.country IN ('USA')
  GROUP BY t.pub_id, ta.au_id
  HAVING SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) > 0
  ORDER BY t.pub_id ASC, ta.au_id ASC;

SELECT t.pub_id, ta.au_id,
    COUNT(*) AS "Num books",
    SUM(t.sales * t.price * r.royalty_rate * ta.royalty_share) AS "Total royalties share",
    SUM(r.advance * ta.royalty_share) AS "Total advances share",
    SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) AS "Total due to author"
  FROM ((publishers AS p
    INNER JOIN titles AS t
      ON p.pub_id = t.pub_id)
      INNER JOIN royalties AS r
        ON t.title_id = r.title_id)
  INNER JOIN title_authors AS ta
    ON t.title_id = ta.title_id
  WHERE t.sales IS NOT NULL
    AND p.country IN ('USA')
  GROUP BY t.pub_id, ta.au_id
  HAVING SUM((t.sales * t.price * r.royalty_rate * ta.royalty_share) - (r.advance * ta.royalty_share)) > 0
  ORDER BY t.pub_id ASC, ta.au_id ASC;

-- Page 238
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city = p.city;

-- Page 239
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city *= p.city
  ORDER BY p.pub_name ASC, a.au_lname ASC, a.au_fname ASC;

SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city = p.city (+)
  ORDER BY p.pub_name ASC, a.au_lname ASC, a.au_fname ASC;

-- Page 240
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city =* p.city
  ORDER BY p.pub_name ASC, a.au_lname ASC, a.au_fname ASC;

SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city (+) = p.city
  ORDER BY p.pub_name ASC, a.au_lname ASC, a.au_fname ASC;

-- Page 241
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city *= p.city
UNION ALL
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city =* p.city
    AND a.city IS NULL;

-- Page 242
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city = p.city (+)
UNION ALL
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a, publishers p
  WHERE a.city (+) = p.city
    AND a.city IS NULL;

SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a
  LEFT OUTER JOIN publishers p
    ON a.city = p.city
UNION ALL
SELECT a.au_fname, a.au_lname, p.pub_name
  FROM authors a
  RIGHT OUTER JOIN publishers p
    ON a.city = p.city
  WHERE a.city IS NULL;

-- Page 243
SELECT a.au_id,
    COUNT(ta.title_id) AS "Num books"
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id (+)
  GROUP BY a.au_id
  ORDER BY a.au_id ASC;

-- Page 244
SELECT a.au_id, a.au_fname, a.au_lname
  FROM authors a, title_authors ta
  WHERE a.au_id = ta.au_id (+)
  AND ta.au_id IS NULL;

-- Page 246
SELECT a.au_id, a.au_fname, a.au_lname, tta.title_id, tta.title_name, tta.sales
  FROM authors a,
    (SELECT ta.au_id, t.title_id, t.title_name, t.sales
       FROM title_authors ta, titles t
       WHERE t.title_id = ta.title_id
         AND sales > 100000) tta
  WHERE a.au_id = tta.au_id (+)
  ORDER BY a.au_id ASC, tta.title_id ASC;

CREATE TEMPORARY TABLE tta
  SELECT ta.au_id, t.title_id, t.title_name, t.sales
  FROM title_authors ta
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  WHERE sales > 100000;

SELECT a.au_id, a.au_fname, a.au_lname, tta.title_id, tta.title_name, tta.sales
  FROM authors a
  LEFT OUTER JOIN tta
    ON a.au_id = tta.au_id
  ORDER BY a.au_id ASC, tta.title_id ASC;

DROP TABLE tta;

-- Page 249
SELECT a1.au_id, a1.au_fname, a1.au_lname, a1.state
  FROM authors a1, authors a2
  WHERE a1.state = a2.state
    AND a2.au_id = 'A04';

SELECT au_id, au_fname, au_lname, state
  FROM authors
  WHERE state IN (SELECT state FROM authors WHERE au_id = 'A04');

-- Page 250
SELECT t1.title_id, t1.sales,
    t2.title_id AS "Better seller",
    t2.sales AS "Higher sales"
  FROM titles t1, titles t2
  WHERE t1.sales < t2.sales
    AND t1.type = 'biography'
    AND t2.type = 'biography'
  ORDER BY t1.title_id ASC, t2.sales ASC;

-- Page 251
SELECT a1.au_fname, a1.au_lname, a2.au_fname, a2.au_lname
  FROM authors a1, authors a2
  WHERE a1.state = a2.state
    AND a1.state = 'NY'
  ORDER BY a1.au_id ASC, a2.au_id ASC;

-- Page 252
SELECT a1.au_fname, a1.au_lname, a2.au_fname, a2.au_lname
  FROM authors a1, authors a2
  WHERE a1.state = a2.state
    AND a1.au_id <> a2.au_id
    AND a1.state = 'NY'
  ORDER BY a1.au_id ASC, a2.au_id ASC;

SELECT a1.au_fname, a1.au_lname, a2.au_fname, a2.au_lname
  FROM authors a1, authors a2
  WHERE a1.state = a2.state
    AND a1.au_id < a2.au_id
    AND a1.state = 'NY'
  ORDER BY a1.au_id ASC, a2.au_id ASC;

-- Page 261
SELECT a.au_id, a.city, p.pub_id
  FROM authors a
  WHERE a.city IN
    (SELECT p.city
       FROM publishers p); --Illegal

-- Page 265
SELECT AVG(sales)
  FROM titles average
  WHERE average.type = 'history';

SELECT AVG(sales)
  FROM titles average
  WHERE average.type = 'history';

SELECT AVG(sales)
  FROM titles average
  WHERE average.type = 'computer';

-- Page 269
SELECT col
  FROM table2
  WHERE NOT col IN
    (SELECT col FROM table1);

SELECT col
  FROM table2
  WHERE NOT ((col = 1)
          OR (col = 2)
          OR (col = NULL));

SELECT col
  FROM table2
  WHERE (col <> 1)
    AND (col <> 2)
    AND (col <> NULL);

SELECT col
  FROM table2
  WHERE col NOT IN
    (SELECT col
       FROM table1
       WHERE col IS NOT NULL);

-- Page 274
SELECT title_id,
    MIN(CASE au_order WHEN 1 THEN au_id END) AS "Author 1",
    MIN(CASE au_order WHEN 2 THEN au_id END) AS "Author 2",
    MIN(CASE au_order WHEN 3 THEN au_id END) AS "Author 3"
  FROM title_authors
  GROUP BY title_id
  ORDER BY title_id ASC;

-- Page 282
SELECT DISTINCT pub_name
  FROM publishers p
  INNER JOIN titles t
    ON p.pub_id = t.pub_id
   AND type = 'biography';

-- Page 284
SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  INNER JOIN titles t
    ON t.title_id = ta.title_id
  WHERE type = 'biography';

SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  WHERE state = 'CA'
    AND royalty_share < 0.5
    AND au_order > 1;

-- Page 286
SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta1
    ON a.au_id = ta1.au_id
  INNER JOIN title_authors ta2
    ON a.au_id = ta2.au_id
  WHERE ta1.royalty_share < 1.0
    AND ta2.royalty_share = 1.0;

SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  WHERE ta.royalty_share < 1.0
INTERSECT
SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  WHERE ta.royalty_share = 1.0;

-- Page 287
SELECT DISTINCT t1.type
  FROM titles t1
  INNER JOIN titles t2
    ON t1.type = t2.type
    AND t1.pub_id <> t2.pub_id;

SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM (authors AS a
    INNER JOIN title_authors AS ta1
      ON a.au_id = ta1.au_id)
  INNER JOIN title_authors AS ta2
    ON a.au_id = ta2.au_id
  WHERE ta1.royalty_share < 1.0
  AND ta2.royalty_share = 1.0;

SELECT au_id, city, state
  FROM authors
  WHERE (city, state) IN (SELECT city, state FROM publishers);

-- Page 289
SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city NOT IN (SELECT city FROM publishers);

-- Page 290
SELECT title_id
  FROM titles
  GROUP BY title_id
  HAVING MAX(sales) >
    (SELECT MAX(sales)
       FROM title_authors ta
       INNER JOIN titles t
         ON t.title_id = ta.title_id
       WHERE ta.au_id = 'A06');

-- Page 292
SELECT au_id, au_lname, au_fname, city
  FROM authors
  WHERE city IN (SELECT city FROM publishers);

-- Page 293
SELECT title_id
  FROM titles
  GROUP BY title_id
  HAVING MIN(sales) >
    (SELECT MIN(sales)
       FROM title_authors ta
       INNER JOIN titles t
         ON t.title_id = ta.title_id
       WHERE ta.au_id = 'A06');

-- Page 297
SELECT DISTINCT a.city
  FROM authors a
  INNER JOIN publishers p
  ON a.city = p.city;

-- Page 297
SELECT DISTINCT city
  FROM authors
  WHERE city NOT IN (SELECT city FROM publishers);

SELECT DISTINCT a.city
  FROM authors a
  LEFT OUTER JOIN publishers p
    ON a.city = p.city
  WHERE p.city IS NULL;

-- Page 299
SELECT au_id, au_lname, au_fname, city
  FROM authors a
  WHERE (SELECT COUNT(*) FROM publishers p WHERE p.city = a.city) > 0;

-- Page 300
SELECT DISTINCT 'Yes' AS "Duplicates?"
  FROM SYSIBM.SYSDUMMY1
  WHERE EXISTS (SELECT 1 FROM authors GROUP BY au_id HAVING COUNT(*) > 1);

-- Page 311
SELECT DISTINCT authors.city
  FROM authors
  INNER JOIN publishers
    ON authors.city = publishers.city;

SELECT DISTINCT city
  FROM authors
  WHERE EXISTS (SELECT * FROM publishers WHERE authors.city = publishers.city);

-- Page 313
SELECT DISTINCT a.city
  FROM authors a
  LEFT OUTER JOIN publishers p
    ON a.city = p.city
  WHERE p.city IS NULL;

SELECT DISTINCT city
  FROM authors
  WHERE NOT EXISTS (SELECT * FROM publishers WHERE authors.city = publishers.city);

SELECT DISTINCT city
  FROM authors
  WHERE city NOT IN (SELECT city FROM publishers);

SELECT city FROM authors
MINUS
SELECT city FROM publishers;

-- Page 329
UPDATE titles
  SET price = price * CASE type
    WHEN 'history' THEN 1.10
    WHEN 'psychology' THEN 1.20
    ELSE 1
  END;

-- Page 336
DELETE FROM titles
  WHERE NOT EXISTS (SELECT * FROM publishers WHERE publishers.pub_id = titles.pub_id);

DELETE FROM titles
  WHERE pub_id NOT IN (SELECT pub_id FROM publishers);

-- Page 345
INSERT INTO authors(au_id, au_fname, au_lname) VALUES('A08', 'Michael', 'Polk');

-- Page 357
CONSTRAINT out_of_print_fk
  FOREIGN KEY (title_id, au_id) REFERENCES title_authors(title_id, au_id)

-- Page 371
CREATE GLOBAL TEMPORARY TABLE sales_today AS
  SELECT * FROM orders WHERE order_date = CURRENT_DATE;

SELECT *
  INTO authors2
  FROM authors;

SELECT *
  INTO publishers2
  FROM publishers
  WHERE 1 = 2;

SELECT title_name, sales
  INTO titles2
  FROM titles
  WHERE pub_id='P01';

SELECT a.au_fname, a.au_lname, t.title_name
  INTO author_title_names
  FROM titles t
  INNER JOIN (authors a
    INNER JOIN title_authors ta
      ON a.au_id = ta.au_id)
    ON t.title_id = ta.title_id
  WHERE a.state NOT IN ('NY','CA');

-- Page 372
SELECT *
  INTO authors2
  FROM authors;

SELECT *
  INTO publishers2
  FROM publishers
  WHERE 1 = 2;

SELECT title_name, sales
  INTO ##titles2
  FROM titles
  WHERE pub_id = 'P01';

SELECT a.au_fname, a.au_lname, t.title_name
  INTO author_title_names
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  INNER JOIN titles t
    ON ta.title_id = t.title_id
  WHERE a.state NOT IN ('CA', 'NY');

CREATE TABLE author_title_names AS
  SELECT a.au_fname, a.au_lname, t.title_name
    FROM authors a, title_authors ta, titles t
    WHERE a.au_id = ta.au_id
      AND ta.title_id = t.title_id
      AND a.state NOT IN ('CA', 'NY');

CREATE TABLE publishers2 AS
  (SELECT * FROM publishers)
  WITH NO DATA;

-- Page 377
SELECT *
  FROM authors
  WHERE au_lname = 'Hull';

-- Page 390
CREATE VIEW au_titles (LastName, Title) AS
  SELECT an.au_lname, t.title_name
  FROM au_names an
  INNER JOIN (titles t
    INNER JOIN title_authors ta
      ON t.title_id = ta.title_id)
    ON an.au_id = ta.au_id
  WHERE an.au_id IN ('A02','A05');

CREATE VIEW cities (au_id, au_city, pub_id, pub_city) AS
  SELECT a.au_id, a.city, p.pub_id, p.city
    FROM authors a, publishers p
    WHERE a.city = p.city;

CREATE VIEW au_titles (LastName, Title) AS
  SELECT an.au_lname, t.title_name
  FROM title_authors ta, au_names an, titles t
  WHERE ta.au_id = an.au_id
    AND t.title_id = ta.title_id
    AND an.au_id in ('A02','A05');

-- Page 392
SELECT ["address3"]
  FROM mailing_labels
  WHERE ["address1"] LIKE '%Kell%';

SELECT "address3"
  FROM mailing_labels
  WHERE "address1" LIKE '%Kell%';

-- Page 395
CREATE VIEW ny_authors AS
  SELECT au_id, au_fname, au_lname, state
    FROM authors
    WHERE state = 'NY'
    WITH CHECK OPTION;

-- Page 396
UPDATE ny_authors
  SET au_fname = 'Yasmin',
      au_lname = 'Howcomely',
      state = 'CA'
  WHERE au_id = 'A01';

-- Page 408
SELECT title_id, sales, SUM(sales) OVER (ORDER BY title_id) AS RunSum
  FROM titles
  ORDER BY title_id;

-- Page 410
INSERT INTO shipment(part_num, desc, quantity)
  VALUES(NEXT VALUE FOR part_seq, 'motherboard', 5);

CREATE TABLE parts (
  part_num INTEGER AS IDENTITY(INCREMENT BY 1 MINVALUE 1 MAXVALUE 10000 START WITH 1 NO CYCLE),
  desc AS VARCHAR(100),
  quantity INTEGER;

INSERT INTO shipment(desc, quantity)
  VALUES(‘motherboard’, 5);

-- Page 419
SELECT DISTINCT t1.id
  FROM temps t1, temps t2
  WHERE t1.hi_temp = 50
    AND t2.hi_temp = 50
    AND ABS(t1.id - t2.id) = 1;

-- Page 422
SELECT *
  FROM (
    SELECT TOP n *
      FROM (
        SELECT TOP n + skip *
          FROM table
          ORDER BY sort_col DESC)
      ORDER BY sort_col ASC)
  ORDER BY sort_col DESC;

-- Page 424
SELECT *
  FROM (
    SELECT TOP n *
      FROM (
        SELECT TOP n + skip *
          FROM table
          ORDER BY sort_col DESC) AS any_name1
      ORDER BY sort_col ASC) AS any_name2
  ORDER BY sort_col DESC;

-- Page 425
SELECT *
  FROM (SELECT ROW_NUMBER() OVER (ORDER BY sort_col DESC) AS rnum, columns FROM table)
  WHERE rnum > skip
    AND rnum <= (n + skip);

-- Page 426
SELECT *
  FROM (SELECT ROW_NUMBER() OVER (ORDER BY sort_col DESC) AS rnum, columns FROM table) AS any_name
  WHERE rnum > skip
  AND rnum <= n + skip;

-- Page 429
SELECT emp_id, sales
  FROM empsales e1
  WHERE (SELECT COUNT(*) FROM empsales e2 WHERE e2.sales > e1.sales) < 3;

-- Page 431
SET @rownum = 0;
SET @rank = 0;
SET @prev_val = NULL;
SELECT
    @rownum := @rownum + 1 AS row,
    @rank := IF(@prev_val <> sales,
    @rownum, @rank) AS rank,
    @prev_val := sales AS sales
  FROM empsales
  ORDER BY sales DESC;

-- Page 434
SELECT TOP n title_id, type, sales
  FROM titles
  ORDER BY NEWID();

SELECT *
  FROM (SELECT title_id, type, sales FROM titles ORDER BY DBMS_RANDOM.VALUE())
  WHERE ROWNUM <= n;

SELECT *
  FROM table
  WHERE (ROWID,0) IN (SELECT ROWID, MOD(ROWNUM,3) FROM table);

-- Page 441
SELECT table_name, comments
  FROM dictionary
  ORDER BY table_name;

-- Page 461
WITH recurse (chain, emp_level, boss_id) AS
  (SELECT CAST(emp_title AS VARCHAR(50)), 0, boss_id
     FROM hier
     WHERE emp_title = 'WS3'
   UNION ALL
   SELECT CAST(recurse.chain || ' < ' || hier.emp_title AS VARCHAR(50)), recurse.emp_level + 1, hier.boss_id
     FROM hier, recurse
     WHERE recurse.boss_id = hier.emp_id)
SELECT chain AS chain_of_command
  FROM recurse
  WHERE emp_level = 3;

WITH recurse (emp_title, emp_id) AS
  (SELECT emp_title,emp_id
     FROM hier
     WHERE emp_title = 'VP1'
   UNION ALL
   SELECT hier.emp_title, hier.emp_id
     FROM hier, recurse
     WHERE recurse.emp_id = hier.boss_id)
SELECT emp_title AS "Works for VP1"
  FROM recurse
  WHERE emp_title <> 'VP1';

SELECT LTRIM(SYS_CONNECT_BY_PATH(emp_title, ' < '), ' < ') AS chain_of_command
  FROM hier
  WHERE LEVEL = 4
  START WITH emp_title = 'WS3'
  CONNECT BY PRIOR boss_id = emp_id;

SELECT emp_title AS "Works for VP1"
  FROM hier
  WHERE emp_title <> 'VP1'
  START WITH emp_title = 'VP1'
  CONNECT BY PRIOR emp_id = boss_id;

-- Page 462
WITH recurse (emp_title, emp_id) AS
  (SELECT CAST(emp_title AS VARCHAR(50)), emp_id
     FROM hier
     WHERE boss_id IS NULL
   UNION ALL
   SELECT CAST(recurse.emp_title || ' > ' || h1.emp_title AS VARCHAR(50)), h1.emp_id
     FROM hier h1, recurse
     WHERE h1.boss_id = recurse.emp_id)
SELECT emp_title emp_tree
  FROM recurse;

-- Page 463
SELECT ltrim(SYS_CONNECT_BY_PATH( emp_title, ' > '),' > ') AS chains_of_command
  FROM hier
  START WITH boss_id IS NULL
  CONNECT BY PRIOR emp_id = boss_id;

-- Page 464
SELECT
    emp_title,
    (CASE CONNECT_BY_ROOT(emp_title) WHEN emp_title THEN 1 ELSE 0 END) AS root_node,
    (SELECT COUNT(*)
       FROM hier h1
       WHERE h1.boss_id = hier.emp_id
         AND hier.boss_id IS NOT NULL
         AND rownum = 1) AS branch_node,
    CONNECT_BY_ISLEAF AS leaf_node
  FROM hier
  START WITH boss_id IS NULL
  CONNECT BY PRIOR emp_id = boss_id
  ORDER BY root_node DESC, branch_node DESC;