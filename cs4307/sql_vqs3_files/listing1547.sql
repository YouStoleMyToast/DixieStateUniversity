-- Extract parts of the current datetime.
SELECT
    to_number(to_char(sysdate,'ss'))   AS sec_pt,
    to_number(to_char(sysdate,'mi'))   AS min_pt,
    to_number(to_char(sysdate,'hh24')) AS hr_pt,
    to_number(to_char(sysdate,'dd'))   AS day_pt,
    to_number(to_char(sysdate,'mm'))   AS mon_pt,
    to_number(to_char(sysdate,'yyyy')) AS yr_pt
 FROM dual;

-- Add or subtract days, months, and years.
SELECT
    pubdate+2               AS p2d,
    pubdate-2               AS m2d,
    add_months(pubdate,+2)  AS p2m,
    add_months(pubdate,-2)  AS m2m,
    add_months(pubdate,+24) AS p2y,
    add_months(pubdate,-24) AS m2y
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
SELECT months_between(date2,date1) AS months
  FROM
    (SELECT
         MIN(pubdate) AS date1,
         MAX(pubdate) AS date2
       FROM titles) t1;