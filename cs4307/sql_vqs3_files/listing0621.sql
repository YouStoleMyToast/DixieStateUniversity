SELECT 
    pub_id,
    type,
    COUNT(*) AS "COUNT(*)"
  FROM titles
  GROUP BY pub_id, type
  HAVING COUNT(*) > 1
  ORDER BY pub_id ASC, "COUNT(*)" DESC;