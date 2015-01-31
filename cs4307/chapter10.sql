#########  Chapter 10  ###############


########   Insert  ############
# Insert New records (whole)
INSERT INTO authors
  VALUES(
    'A08',
    'Michael',
    'Polk',
    '512-953-1231',
    '4028 Guadalupe St',
    'Austin',
    'TX',
    '78701');


# Insert New records (Partial fields)
INSERT INTO authors(
    au_id,
    au_fname,
    au_lname,
    phone,
    address,
    city,
    state,
    zip)
  VALUES(
    'A09',
    'Irene',
    'Bell',
    '415-225-4689',
    '810 Throckmorton Ave',
    'Mill Valley',
    'CA',
    '94941');

# Insert new records (Multiple Records)
insert into authors values
   ('A11','Bill','Green','415-555-1212','123 Here Street','Hereville','UT','55555'),
   ('A12','Bob','Throw','415-555-1212','123 There Street','SG','UT','55555');

# Insert records from another table
create table new_authors as
   (select * from authors where FALSE);
insert into new_authors values
   ('A13','Bill','Green','415-555-1212','123 Here Street','Hereville','UT','55555'),
   ('A14','Bob','Throw','415-555-1212','123 There Street','SG','UT','55555');
insert into authors
   (select * from new_authors);


######################  Updates ########################
# Double the price of all history books
UPDATE titles
  SET price = price * 2.0
  WHERE type = 'history';
#  Change type of psychology books to self help and change the page number to NULL
UPDATE titles
  SET type = 'self help',
      pages = NULL
  WHERE type = 'psychology';


####################  Deletes #########################
####referential integrity-no missing links from/to other tables
# Delete all records
DELETE FROM royalties;
TRUNCATE TABLE ROYALTIES;

# Delete publishers P01 & P02
DELETE FROM title_authors
  WHERE title_id IN
    (SELECT title_id
      FROM titles
      WHERE pub_id IN ('P01', 'P04'));

#  Delete missing links (Referential Integrity)
DELETE FROM titles
  WHERE NOT EXISTS
      (SELECT * FROM publishers WHERE publishers.pub_id = titles.pub_id);
DELETE FROM titles
  WHERE pub_id NOT IN (SELECT pub_id FROM publishers);



