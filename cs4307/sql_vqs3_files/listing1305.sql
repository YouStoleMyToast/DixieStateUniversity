CREATE VIEW au_titles (LastName, Title)
  AS
  SELECT an.au_lname, t.title_name
    FROM title_authors ta
    INNER JOIN au_names an
      ON ta.au_id = an.au_id
    INNER JOIN titles t
      ON t.title_id = ta.title_id
    WHERE an.au_id in ('A02','A05');