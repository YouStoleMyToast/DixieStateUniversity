SELECT DISTINCT 'Yes' AS "Duplicates?"
  WHERE EXISTS
    (SELECT *
      FROM title_authors
      GROUP BY au_id
      HAVING COUNT(*) > 1);