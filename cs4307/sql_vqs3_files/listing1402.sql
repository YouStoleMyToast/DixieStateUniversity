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