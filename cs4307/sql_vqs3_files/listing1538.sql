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