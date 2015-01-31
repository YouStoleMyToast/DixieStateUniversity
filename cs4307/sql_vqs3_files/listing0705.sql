SELECT
    title_id,
    pub_id,
    pub_name
  FROM publishers
  NATURAL JOIN titles;