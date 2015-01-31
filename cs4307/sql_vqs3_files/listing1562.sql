SELECT chain AS chains_of_command
  FROM
    (SELECT emp_title as chain
       FROM hier
       WHERE boss_id IS NULL
     UNION
     SELECT
         h1.emp_title || ' > ' ||
         h2.emp_title
       FROM hier h1
       INNER JOIN hier h2
         ON (h1.emp_id = h2.boss_id)
       WHERE h1.boss_id IS NULL
     UNION
     SELECT
         h1.emp_title || ' > ' ||
         h2.emp_title || ' > ' ||
         h3.emp_title
       FROM hier h1
       INNER JOIN hier h2
         ON (h1.emp_id = h2.boss_id)
       LEFT OUTER JOIN hier h3
         ON (h2.emp_id = h3.boss_id)
       WHERE h1.emp_title = 'CEO'
     UNION
     SELECT
         h1.emp_title || ' > ' ||
         h2.emp_title || ' > ' ||
         h3.emp_title || ' > ' ||
         h4.emp_title
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