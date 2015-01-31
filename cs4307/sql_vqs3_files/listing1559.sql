SELECT
    au_ids.au_id,
    CASE au_ids.au_id
      WHEN 'A01' THEN num_books.A01
      WHEN 'A02' THEN num_books.A02
      WHEN 'A03' THEN num_books.A03
      WHEN 'A04' THEN num_books.A04
      WHEN 'A05' THEN num_books.A05
      WHEN 'A06' THEN num_books.A06
      WHEN 'A07' THEN num_books.A07
    END
      AS num_books
  FROM
    (SELECT au_id FROM authors) au_ids,
    (SELECT
         SUM(CASE WHEN au_id='A01' THEN 1 ELSE 0 END) AS A01,
         SUM(CASE WHEN au_id='A02' THEN 1 ELSE 0 END) AS A02,
         SUM(CASE WHEN au_id='A03' THEN 1 ELSE 0 END) AS A03,
         SUM(CASE WHEN au_id='A04' THEN 1 ELSE 0 END) AS A04,
         SUM(CASE WHEN au_id='A05' THEN 1 ELSE 0 END) AS A05,
         SUM(CASE WHEN au_id='A06' THEN 1 ELSE 0 END) AS A06,
         SUM(CASE WHEN au_id='A07' THEN 1 ELSE 0 END) AS A07
       FROM title_authors) num_books;