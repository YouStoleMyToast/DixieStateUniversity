CREATE TABLE titles
  (
  title_id   CHAR(3)                          NOT NULL,
  title_name VARCHAR(40)  DEFAULT ' '         NOT NULL,
  type       VARCHAR(10)  DEFAULT 'undefined'         ,
  pub_id     CHAR(3)                          NOT NULL,
  pages      INTEGER      DEFAULT NULL                ,
  price      DECIMAL(5,2) DEFAULT 0.00        NOT NULL,
  sales      INTEGER                                  ,
  pubdate    DATE         DEFAULT SYSDATE             ,
  contract   SMALLINT     DEFAULT (3*7)-21    NOT NULL
  );