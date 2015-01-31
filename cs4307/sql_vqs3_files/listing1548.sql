-- Extract parts of the current datetime.
SELECT
    second(current_timestamp) AS sec_pt,
    minute(current_timestamp) AS min_pt,
    hour(current_timestamp)   AS hr_pt,
    day(current_timestamp)    AS day_pt,
    month(current_timestamp)  AS mon_pt,
    year(current_timestamp)   AS yr_pt
  FROM SYSIBM.SYSDUMMY1;

-- Add or subtract days, months, and years.
SELECT
    pubdate + 2 DAY   AS p2d,
    pubdate - 2 DAY   AS m2d,
    pubdate + 2 MONTH AS p2m,
    pubdate - 2 MONTH AS m2m,
    pubdate + 2 YEAR  AS p2y,
    pubdate - 2 YEAR  AS m2y
  FROM titles
  WHERE title_id = 'T05';

-- Count the days between two dates.
SELECT days(date2) - days(date1) AS days
  FROM
    (SELECT pubdate as date1
       FROM titles
       WHERE title_id = 'T05') t1,
    (SELECT pubdate as date2
       FROM titles
       WHERE title_id = 'T06') t2;

-- Count the months between two dates.
SELECT
    (year(date2)*12 + month(date2)) -
    (year(date1)*12 + month(date1))
      AS months
  FROM
    (SELECT
         MIN(pubdate) AS date1,
         MAX(pubdate) AS date2
       FROM titles) t1;