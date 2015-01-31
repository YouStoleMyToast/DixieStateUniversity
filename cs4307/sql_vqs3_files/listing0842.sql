SELECT DISTINCT t1.type
  FROM titles t1
  WHERE t1.type IN
    (SELECT t2.type
      FROM titles t2
      WHERE t1.pub_id <> t2.pub_id);