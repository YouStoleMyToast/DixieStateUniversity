SELECT
    candidate.title_id,
    candidate.type,
    candidate.sales
  FROM titles candidate
  WHERE sales >=
    (SELECT AVG(sales)
      FROM titles average
      WHERE average.type = candidate.type);