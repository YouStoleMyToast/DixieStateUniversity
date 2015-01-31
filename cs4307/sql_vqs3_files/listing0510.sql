SELECT 'Title '
       || title_id
       || ' published on '
       || CAST(pubdate AS CHAR(10))
         AS "Biography publication dates"
  FROM titles
  WHERE type = 'biography'
    AND pubdate IS NOT NULL
  ORDER BY pubdate DESC;