SELECT DISTINCT 'Yes' AS "Duplicates?"
  WHERE EXISTS
    (SELECT *
      FROM authors
      GROUP BY au_id
      HAVING COUNT(*) > 1);