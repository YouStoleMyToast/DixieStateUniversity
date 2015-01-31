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