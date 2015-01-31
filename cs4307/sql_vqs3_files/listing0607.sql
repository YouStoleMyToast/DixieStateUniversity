SELECT COUNT(au_id)
         AS "COUNT(au_id)"
  FROM title_authors;

SELECT DISTINCT COUNT(au_id)
         AS "DISTINCT COUNT(au_id)"
  FROM title_authors;

SELECT COUNT(DISTINCT au_id)
         AS "COUNT(DISTINCT au_id)"
  FROM title_authors;