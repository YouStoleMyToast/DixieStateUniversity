CREATE VIEW ny_authors
  AS
  SELECT au_id, au_fname, au_lname, state
    FROM authors
    WHERE state = 'NY';

SELECT *
  FROM ny_authors;