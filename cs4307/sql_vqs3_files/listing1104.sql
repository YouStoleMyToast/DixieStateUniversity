CREATE TABLE titles
  (
  title_id   CHAR(3)      NOT NULL,
  title_name VARCHAR(40)  NOT NULL,
  type       VARCHAR(10)  NULL    ,
  pub_id     CHAR(3)      NOT NULL,
  pages      INTEGER      NULL    ,
  price      DECIMAL(5,2) NULL    ,
  sales      INTEGER      NULL    ,
  pubdate    DATE         NULL    ,
  contract   SMALLINT     NOT NULL
  );