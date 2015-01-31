SELECT pub_id, pub_name, state, country
  FROM publishers
  WHERE (state = 'CA')
     OR (state <> 'CA');