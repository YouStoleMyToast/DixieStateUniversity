SELECT title_id, advance
  FROM royalties
  WHERE advance IN (
    (SELECT MIN(advance) FROM royalties),
    (SELECT MAX(advance) FROM royalties));