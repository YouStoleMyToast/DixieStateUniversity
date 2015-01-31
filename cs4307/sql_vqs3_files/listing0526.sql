SELECT title_id, pubdate
  FROM titles
  WHERE pubdate 
        BETWEEN CURRENT_TIMESTAMP
                - INTERVAL 90 DAY
            AND CURRENT_TIMESTAMP
                + INTERVAL 90 DAY
     OR pubdate IS NULL
  ORDER BY pubdate DESC;