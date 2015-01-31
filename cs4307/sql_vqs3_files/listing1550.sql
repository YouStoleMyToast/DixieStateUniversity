-- Extract parts of the current datetime.
SELECT
  date_part('second',current_timestamp) AS sec_pt,
  date_part('minute',current_timestamp) AS min_pt,
  date_part('hour',current_timestamp)   AS hr_pt,
  date_part('day',current_timestamp)    AS day_pt,
  date_part('month',current_timestamp)  AS mon_pt,
  date_part('year',current_timestamp)   AS yr_pt;

-- Add or subtract days, months, and years.
SELECT
    pubdate + INTERVAL '2 DAY'   AS p2d,
    pubdate - INTERVAL '2 DAY'   AS m2d,
    pubdate + INTERVAL '2 MONTH' AS p2m,
    pubdate - INTERVAL '2 MONTH' AS m2m,
    pubdate + INTERVAL '2 YEAR'  AS p2y,
    pubdate - INTERVAL '2 YEAR'  AS m2y
  FROM titles
  WHERE title_id = 'T05';

-- Count the days between two dates.
SELECT date2 - date1 AS days
  FROM
    (SELECT pubdate as date1
       FROM titles
       WHERE title_id = 'T05') t1,
    (SELECT pubdate as date2
       FROM titles
       WHERE title_id = 'T06') t2;

-- Count the months between two dates.
SELECT
    (date_part('year',date2)*12 + date_part('month',date2)) -
    (date_part('year',date1)*12 + date_part('month',date1))
      AS months
  FROM
    (SELECT
         MIN(pubdate) AS date1,
         MAX(pubdate) AS date2
       FROM titles) t1;