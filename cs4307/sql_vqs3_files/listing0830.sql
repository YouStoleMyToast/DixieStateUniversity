SELECT ta1.au_id, ta1.title_id,
    ta1.royalty_share
  FROM title_authors ta1
  WHERE ta1.royalty_share <
    (SELECT MAX(ta2.royalty_share)
      FROM title_authors ta2
      WHERE ta1.title_id = ta2.title_id);