CREATE VIEW revenues
  (Publisher, BookType, Revenue)
  AS
  SELECT pub_id, type, SUM(price * sales)
    FROM titles
    GROUP BY pub_id, type;