SELECT DISTINCT a.au_id, au_fname, au_lname
  FROM authors a
  INNER JOIN title_authors ta
    ON a.au_id = ta.au_id
  WHERE ta.royalty_share < 1.0
    AND a.au_id IN
      (SELECT a.au_id
        FROM authors a
        INNER JOIN title_authors ta
          ON a.au_id = ta.au_id
        AND ta.royalty_share = 1.0);