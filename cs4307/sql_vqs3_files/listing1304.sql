CREATE VIEW mailing_labels
  AS
  SELECT
      TRIM(au_fname || ' ' || au_lname)
        AS "address1",
      TRIM(address)
        AS "address2",
      TRIM(city) || ', ' || TRIM(state) ||
        ' ' || TRIM(zip)
        AS "address3"
    FROM authors;