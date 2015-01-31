-- Extract parts of the current datetime.
SELECT
  datepart("s",   getdate()) AS sec_pt,
  datepart("n",   getdate()) AS min_pt,
  datepart("hh",  getdate()) AS hr_pt,
  datepart("d",   getdate()) AS day_pt,
  datepart("m",   getdate()) AS mon_pt,
  datepart("yyyy",getdate()) AS yr_pt;

-- Add or subtract days, months, and years.
SELECT
    dateadd("d",    2,pubdate) AS p2d,
    dateadd("d",   -2,pubdate) AS m2d,
    dateadd("m",    2,pubdate) AS p2m,
    dateadd("m",   -2,pubdate) AS m2m,
    dateadd("yyyy", 2,pubdate) AS p2y,
    dateadd("yyyy",-2,pubdate) AS m2y
  FROM titles
  WHERE title_id = 'T05';

-- Count the days between two dates.
SELECT datediff("d",date1,date2) AS days
  FROM
    (SELECT pubdate as date1
       FROM titles
       WHERE title_id = 'T05') t1,
    (SELECT pubdate as date2
       FROM titles
       WHERE title_id = 'T06') t2;

-- Count the months between two dates.
SELECT datediff("m",date1,date2) AS months
  FROM
    (SELECT
         MIN(pubdate) AS date1,
         MAX(pubdate) AS date2
       FROM titles) t1;