SELECT pub_id,
       SUBSTRING(pub_id FROM 1 FOR 1)
         AS "Alpha part",
       SUBSTRING(pub_id FROM 2)
         AS "Num part"
  FROM publishers;