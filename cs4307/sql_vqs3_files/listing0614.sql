SELECT
    pub_id,
    type,
    COUNT(*) AS "COUNT(*)"
  FROM titles
  GROUP BY pub_id, type
  ORDER BY pub_id ASC, "COUNT(*)" DESC;