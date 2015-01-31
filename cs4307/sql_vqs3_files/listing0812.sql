SELECT au_id, city
  FROM authors
  WHERE city IN
    ('New York', 'San Francisco',
     'Hamburg', 'Berkeley');