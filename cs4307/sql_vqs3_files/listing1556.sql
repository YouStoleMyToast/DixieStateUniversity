SELECT
    t1.title_id,
    CASE WHEN t1.type = 'biography'
      THEN '*IGNORED*'
      ELSE t1.type END
        AS title_type,
    t1.sales,
    (SELECT
         SUM(CASE WHEN t2.type = 'biography'
               THEN NULL
               ELSE t2.sales END)
       FROM titles t2
       WHERE t1.title_id >= t2.title_id)
         AS RunSum
  FROM titles t1;