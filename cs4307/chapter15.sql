# running totals
SELECT 
    t1.title_id,
    SUM(t2.sales) AS RunSum,
    AVG(t2.sales) AS RunAvg,
    COUNT(t2.sales) AS RunCount
  FROM titles t1, titles t2
  WHERE t1.title_id >= t2.title_id
  GROUP BY t1.title_id
  ORDER BY t1.title_id;

#moving averages
SELECT t1.seq, AVG(t2.price) AS MovingAvg
  FROM time_series t1, time_series t2
  WHERE t1.seq >= 5
    AND t1.seq BETWEEN t2.seq AND t2.seq+4
  GROUP BY t1.seq
  ORDER BY t1.seq;

# difference between two records
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

# sequences
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

# top 3
SELECT emp_id, sales
  FROM empsales
  ORDER BY sales DESC
  LIMIT 3;

# ranks
SELECT e1.emp_id, e1.sales,
    (SELECT COUNT(sales)
       FROM empsales e2
       WHERE e2.sales > e1.sales) + 1
         AS ranking
  FROM empsales e1;

# trimmed means
SELECT AVG(sales) AS TrimmedMean
  FROM titles t1
  WHERE
    (SELECT COUNT(*)
       FROM titles t2
       WHERE t2.sales <= t1.sales) >=
         (SELECT 0.25 * COUNT(*)
            FROM titles)
    AND
    (SELECT COUNT(*)
       FROM titles t3
       WHERE t3.sales >= t1.sales) >=
         (SELECT 0.25 * COUNT(*) 
            FROM titles);


# random rows
SELECT title_id, type, sales
  FROM titles
  WHERE RAND() < 0.25;

#dups
SELECT title_name, type, price
  FROM dups
  GROUP BY title_name, type, price
  HAVING COUNT(*) > 1;

# Coalesce
SELECT
    a.au_id AS "ID",
    a.au_fname AS "FirstName",
    a.au_lname AS "LastName",
    COALESCE(twork.tel_no, thome.tel_no) AS "TelNo",
    COALESCE(twork.tel_type, thome.tel_type) AS "TelType"
  FROM authors a
  LEFT OUTER JOIN telephones twork
    ON a.au_id = twork.au_id
    AND twork.tel_type = 'W'
  LEFT OUTER JOIN telephones thome
    ON a.au_id = thome.au_id
    AND thome.tel_type = 'H'
  WHERE COALESCE(twork.tel_no, thome.tel_no) IS NOT NULL
  ORDER BY a.au_fname ASC, a.au_lname ASC;

# pivoting
SELECT
    SUM(CASE WHEN au_id='A01' THEN 1 ELSE 0 END) AS A01,
    SUM(CASE WHEN au_id='A02' THEN 1 ELSE 0 END) AS A02,
    SUM(CASE WHEN au_id='A03' THEN 1 ELSE 0 END) AS A03,
    SUM(CASE WHEN au_id='A04' THEN 1 ELSE 0 END) AS A04,
    SUM(CASE WHEN au_id='A05' THEN 1 ELSE 0 END) AS A05,
    SUM(CASE WHEN au_id='A06' THEN 1 ELSE 0 END) AS A06,
    SUM(CASE WHEN au_id='A07' THEN 1 ELSE 0 END) AS A07
  FROM title_authors;

# hierarchies
SELECT concat(h1.emp_title,' obeys ',h2.emp_title)
    AS power_structure
  FROM hier h1, hier h2
  WHERE h1.boss_id = h2.emp_id;

SELECT chain AS chains_of_command
  FROM
    (SELECT emp_title as chain
       FROM hier
       WHERE boss_id IS NULL
     UNION
     SELECT
         concat(h1.emp_title ,' > ',
         h2.emp_title)
       FROM hier h1
       INNER JOIN hier h2
         ON (h1.emp_id = h2.boss_id)
       WHERE h1.boss_id IS NULL
     UNION
     SELECT
         concat(h1.emp_title ,' > ',
         h2.emp_title ,' > ' ,
         h3.emp_title)
       FROM hier h1
       INNER JOIN hier h2
         ON (h1.emp_id = h2.boss_id)
       LEFT OUTER JOIN hier h3
         ON (h2.emp_id = h3.boss_id)
       WHERE h1.emp_title = 'CEO'
     UNION
     SELECT
         concat(h1.emp_title , ' > ' ,
         h2.emp_title , ' > ' ,
         h3.emp_title , ' > ' ,
         h4.emp_title)
       FROM hier h1
       INNER JOIN hier h2
         ON (h1.emp_id = h2.boss_id)
       INNER JOIN hier h3
         ON (h2.emp_id = h3.boss_id)
       LEFT OUTER JOIN hier h4
         ON (h3.emp_id = h4.boss_id)
       WHERE h1.emp_title = 'CEO'
    ) chains
   WHERE chain IS NOT NULL
   ORDER BY chain;



