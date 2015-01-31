SELECT
    i AS CharCode,
    CHR(i) AS Ch
  FROM seq
  WHERE i BETWEEN 32 AND 126;