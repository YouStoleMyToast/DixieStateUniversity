# hides personal information
CREATE VIEW au_names
  AS
  SELECT au_id, au_fname, au_lname
    FROM authors;

# cities with an author and publisher
CREATE VIEW cities
  (au_id, au_city, pub_id, pub_city)
  AS
  SELECT a.au_id, a.city, p.pub_id, p.city
    FROM authors a
    INNER JOIN publishers p
      ON a.city = p.city;

# revenues grouped by pub_id then type
CREATE VIEW revenues
  (Publisher, BookType, Revenue)
  AS
  SELECT pub_id, type, SUM(price * sales)
    FROM titles
    GROUP BY pub_id, type;

# mailing labels
CREATE VIEW mailing_labels
  AS
  SELECT
      TRIM(au_fname || ' ' || au_lname)
        AS "address1",
      TRIM(address)
        AS "address2",
      TRIM(city) || ', ' || TRIM(state) ||
        ' ' || TRIM(zip)
        AS "address3"
    FROM authors;

# authors a03 or a05 (nested view)
CREATE VIEW au_titles (LastName, Title)
  AS
  SELECT an.au_lname, t.title_name
    FROM title_authors ta
    INNER JOIN au_names an
      ON ta.au_id = an.au_id
    INNER JOIN titles t
      ON t.title_id = ta.title_id
    WHERE an.au_id in ('A02','A05');

# using a view
SELECT *
  FROM au_titles;
SELECT DISTINCT au_city
  FROM cities;
SELECT BookType,
    AVG(Revenue) AS "AVG(Revenue)"
  FROM revenues
  GROUP BY BookType
  HAVING AVG(Revenue) > 1000000;
SELECT address3
  FROM mailing_labels
  WHERE address1 LIKE '%Kell%';
SELECT DISTINCT an.au_fname, an.au_lname
  FROM au_names an
  INNER JOIN title_authors ta
    ON an.au_id = ta.au_id
  WHERE ta.au_order > 1;
SELECT au_fname, au_lname
  FROM au_names
  WHERE state = 'CA';

# NY authors
CREATE VIEW ny_authors
  AS
  SELECT au_id, au_fname, au_lname, state
    FROM authors
    WHERE state = 'NY';

# updating NY authors
SELECT *
  FROM ny_authors;
INSERT INTO ny_authors
  VALUES('A08','Don','Dawson','NY');
INSERT INTO ny_authors
  VALUES('A09','Jill','LeFlore','CA');
UPDATE ny_authors
  SET au_fname = 'Yasmin',
      au_lname = 'Howcomely'
  WHERE au_id = 'A01';

