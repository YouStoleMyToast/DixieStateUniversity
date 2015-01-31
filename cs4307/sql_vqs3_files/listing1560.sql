SELECT h1.emp_title || ' obeys ' || h2.emp_title
    AS power_structure
  FROM hier h1, hier h2
  WHERE h1.boss_id = h2.emp_id;