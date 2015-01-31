SELECT
    title_id,
    pubdate
  FROM titles
  WHERE EXTRACT(YEAR FROM pubdate)
          BETWEEN 2001 AND 2002
    AND EXTRACT(MONTH FROM pubdate)
          BETWEEN 1 AND 6
  ORDER BY pubdate DESC;