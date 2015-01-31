SELECT au_id,
    (SELECT COUNT(*)
      FROM title_authors ta
      WHERE ta.au_id = a.au_id)
        AS "Num books"
  FROM authors a
  ORDER BY au_id ASC;