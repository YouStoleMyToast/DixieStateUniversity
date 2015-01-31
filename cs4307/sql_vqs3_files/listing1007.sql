INSERT INTO publishers(
    pub_id,
    pub_name,
    city,
    state,
    country)
  SELECT *
    FROM new_publishers
    WHERE pub_name = 'XXX';