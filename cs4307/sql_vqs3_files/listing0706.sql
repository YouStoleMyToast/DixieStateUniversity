SELECT
    title_id,
    pub_id,
    pub_name,
    advance
  FROM publishers
  NATURAL JOIN titles
  NATURAL JOIN royalties
  WHERE advance < 20000;