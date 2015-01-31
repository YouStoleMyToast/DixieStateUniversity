SELECT
  '<' || '  AAA  ' || '>'
    AS "Untrimmed",
  '<' || TRIM(LEADING FROM '  AAA  ') || '>'
    AS "Leading",
  '<' || TRIM(TRAILING FROM '  AAA  ') || '>'
    AS "Trailing",
  '<' || TRIM('  AAA  ') || '>'
     AS "Both";