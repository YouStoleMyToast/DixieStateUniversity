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