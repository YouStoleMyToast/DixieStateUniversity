SELECT SUM(pages), AVG(price) FROM titles;

# this never gets posted because of the rollback
BEGIN TRANSACTION;
  UPDATE titles SET pages = 0;
  UPDATE titles SET price = price * 2;
  SELECT SUM(pages), AVG(price) FROM titles;
ROLLBACK;

SELECT SUM(pages), AVG(price) FROM titles;



# all or none of the deletes take place
BEGIN TRANSACTION;
  DELETE FROM title_authors
    WHERE title_id IN
      (SELECT title_id
         FROM titles
         WHERE pub_id = 'P04');
  DELETE FROM royalties
    WHERE title_id IN
      (SELECT title_id
         FROM titles
         WHERE pub_id = 'P04');
  DELETE FROM titles
    WHERE pub_id = 'P04';
  DELETE FROM publishers
    WHERE pub_id = 'P04';
COMMIT;