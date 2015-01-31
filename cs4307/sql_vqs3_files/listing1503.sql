SELECT
    t1.seq AS seq1,
    t2.seq AS seq2,
    t1.city AS city1,
    t2.city AS city2,
    t1.miles AS miles1,
    t2.miles AS miles2,
    t2.miles - t1.miles AS dist
  FROM roadtrip t1, roadtrip t2
  WHERE t1.seq+1 = t2.seq
  ORDER BY t1.seq;