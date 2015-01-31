SELECT t1.seq, AVG(t2.price) AS MovingAvg
  FROM time_series t1, time_series t2
  WHERE t1.seq >= 5
    AND t1.seq BETWEEN t2.seq AND t2.seq+4
  GROUP BY t1.seq
  ORDER BY t1.seq;