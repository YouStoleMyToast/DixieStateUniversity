SELECT 
   t1.id AS StartSeq,
   t2.id AS EndSeq,
   t2.id - t1.id + 1 AS SeqLen
  FROM temps t1, temps t2
  WHERE (t1.id < t2.id)
    AND NOT EXISTS(
      SELECT *
        FROM temps t3 
        WHERE (t3.hi_temp - t3.id <> 
               t1.hi_temp - t1.id
               AND t3.id BETWEEN
                   t1.id AND t2.id)
           OR (t3.id = t1.id - 1
               AND t3.hi_temp - t3.id = 
                   t1.hi_temp - t1.id) 
           OR (t3.id = t2.id + 1
               AND t3.hi_temp - t3.id = 
                   t1.hi_temp - t1.id)
    );