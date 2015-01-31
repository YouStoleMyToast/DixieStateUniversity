SELECT MIN(price) AS "Min price"
  FROM titles;

SELECT MIN(pubdate) AS "Earliest pubdate"
  FROM titles;

SELECT MIN(pages) AS "Min history pages"
  FROM titles
  WHERE type = 'history';