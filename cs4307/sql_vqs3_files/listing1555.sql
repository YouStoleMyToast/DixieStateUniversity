SELECT title_id, advance
  FROM
    (SELECT title_id, advance,
         MIN(advance) OVER () min_adv,
         MAX(advance) OVER () max_adv
       FROM royalties) t1
  WHERE advance IN (min_adv, max_adv);