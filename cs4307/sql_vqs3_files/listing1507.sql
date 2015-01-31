SELECT
    i AS MonthsAhead,
    DATEADD("m", i, CURRENT_TIMESTAMP)
      AS FutureDate
  FROM seq
  WHERE i BETWEEN 1 AND 6;