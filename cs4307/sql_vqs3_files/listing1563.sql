SELECT h1.emp_title,
  (SELECT SIGN(COUNT(*))
     FROM hier h2
     WHERE h1.emp_id = h2.emp_id
       AND h2.boss_id IS NULL)
         AS root_node,
  (SELECT SIGN(COUNT(*))
     FROM hier h2
     WHERE h1.emp_id = h2.boss_id
       AND h1.boss_id IS NOT NULL)
         AS branch_node,
  (SELECT SIGN(COUNT(*))
     FROM hier h2
     WHERE 0 =
       (SELECT COUNT(*)
          FROM hier h3
          WHERE h1.emp_id = h3.boss_id))
            AS leaf_node
  FROM hier h1;