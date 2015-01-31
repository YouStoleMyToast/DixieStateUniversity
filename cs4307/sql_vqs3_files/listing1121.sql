CREATE TABLE author_title_names AS
  SELECT a.au_fname, a.au_lname,
      t.title_name
    FROM authors a
    INNER JOIN title_authors ta
      ON a.au_id = ta.au_id
    INNER JOIN titles t
      ON ta.title_id = t.title_id
    WHERE a.state NOT IN ('CA', 'NY');