SELECT pub_id, AVG(sales) AS "AVG(sales)"
  FROM titles
  GROUP BY pub_id
  HAVING AVG(sales) >
    (SELECT AVG(sales)
      FROM titles);