SELECT
    t1.id AS StartReg,
    t2.id AS EndReg,
    t2.id - t1.id + 1 AS RegLen
  FROM temps t1, temps t2
  WHERE (t1.id < t2.id)
    AND t2.id - t1.id = 1
    AND NOT EXISTS(
      SELECT *
        FROM temps t3
        WHERE (t3.hi_temp <> 50
          AND t3.id BETWEEN
              t1.id AND t2.id)
    );
