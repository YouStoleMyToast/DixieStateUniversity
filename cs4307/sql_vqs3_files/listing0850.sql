SELECT pub_name
  FROM publishers p
  WHERE EXISTS
    (SELECT *
      FROM titles t
      WHERE t.pub_id = p.pub_id
        AND type = 'biography');