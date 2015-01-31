SELECT SUM(pages), AVG(price) FROM titles;

BEGIN TRANSACTION;
  UPDATE titles SET pages = 0;
  UPDATE titles SET price = price * 2;
  SELECT SUM(pages), AVG(price) FROM titles;
ROLLBACK;

SELECT SUM(pages), AVG(price) FROM titles;