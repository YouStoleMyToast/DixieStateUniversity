DELETE FROM dups
  WHERE id < (
    SELECT MAX(d.id)
     FROM dups d
     WHERE dups.title_name = d.title_name
       AND dups.type = d.type
       AND dups.price = d.price);