SELECT col
  FROM table2
  WHERE col NOT IN
    (SELECT col
      FROM table1);