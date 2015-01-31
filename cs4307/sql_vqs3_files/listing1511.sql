SELECT 
   t1.id AS StartRun,
   t2.id AS EndRun,
   t2.id - t1.id + 1 AS RunLen
  FROM temps t1, temps t2
  WHERE (t1.id < t2.id)
    AND NOT EXISTS(
      SELECT * 
        FROM temps t3, temps t4 
        WHERE (t3.hi_temp <= t4.hi_temp
               AND t4.id = t3.id - 1
               AND t3.id BETWEEN
                   t1.id + 1 AND t2.id) 
           OR (t3.id = t1.id - 1
               AND t3.hi_temp < 
                   t1.hi_temp) 
           OR (t3.id = t2.id + 1
               AND t3.hi_temp > 
                   t2.hi_temp)
    );