CREATE TABLE titles
  (
  title_id   CHAR(3)      NOT NULL,
  title_name VARCHAR(40)  NOT NULL,
  type       VARCHAR(10)
    CONSTRAINT type_chk
      CHECK (type IN ('biography',
        'children','computer',
        'history','psychology'))  ,
  pub_id     CHAR(3)      NOT NULL,
  pages      INTEGER
    CHECK (pages > 0)             ,
  price      DECIMAL(5,2)         ,
  sales      INTEGER              ,
  pubdate    DATE                 ,
  contract   SMALLINT     NOT NULL,
  CONSTRAINT titles_pk
    PRIMARY KEY (title_id),
  CONSTRAINT titles_pub_id_fk
    FOREIGN KEY (pub_id)
    REFERENCES publishers(pub_id),
  CONSTRAINT title_id_chk
    CHECK (
    (SUBSTRING(title_id FROM 1 FOR 1) = 'T')
    AND
    (CAST(SUBSTRING(title_id FROM 2 FOR 2)
    AS INTEGER) BETWEEN 0 AND 99)),
  CONSTRAINT price_chk
    CHECK (price >= 0.00
      AND price < 100.00),
  CONSTRAINT sales_chk
    CHECK (sales >= 0),
  CONSTRAINT pubdate_chk
    CHECK (pubdate >= DATE '1950-01-01'),
  CONSTRAINT title_name_chk
    CHECK (title_name <> ''
      AND contract >= 0),
  CONSTRAINT revenue_chk
    CHECK (price * sales >= 0.00)
  );