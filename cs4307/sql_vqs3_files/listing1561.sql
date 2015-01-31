SELECT
    h1.emp_title || ' < ' ||
    h2.emp_title || ' < ' ||
    h3.emp_title || ' < ' ||
    h4.emp_title
      AS chain_of_command
  FROM hier h1, hier h2, hier h3, hier h4
  WHERE h1.emp_title = 'WS3'
    AND h1.boss_id = h2.emp_id
    AND h2.boss_id = h3.emp_id
    AND h3.boss_id = h4.emp_id;