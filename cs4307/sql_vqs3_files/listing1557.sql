SELECT
    title_id,
    CASE WHEN type = 'biography'
      THEN '*IGNORED*'
      ELSE type END
        AS title_type,
    sales,
    SUM(CASE WHEN type = 'biography'
          THEN NULL
          ELSE sales END)
          OVER (ORDER BY title_id, sales)
      AS RunSum
  FROM titles;