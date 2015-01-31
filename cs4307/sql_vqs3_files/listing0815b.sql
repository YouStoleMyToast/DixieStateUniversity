SELECT pub_name
  FROM publishers
  WHERE publishers.pub_id IN
    (SELECT titles.pub_id
      FROM titles
      WHERE type = 'biography');