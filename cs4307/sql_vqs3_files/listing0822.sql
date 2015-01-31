SELECT MAX(ta.count_titles) AS "Max titles"
  FROM (SELECT COUNT(*) AS count_titles
         FROM title_authors
         GROUP BY au_id) ta;