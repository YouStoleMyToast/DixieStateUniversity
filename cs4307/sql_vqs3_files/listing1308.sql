SELECT BookType,
    AVG(Revenue) AS "AVG(Revenue)"
  FROM revenues
  GROUP BY BookType
  HAVING AVG(Revenue) > 1000000;