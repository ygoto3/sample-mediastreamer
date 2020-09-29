-- +migrate Up
CREATE TABLE IF NOT EXISTS overlays (
  id int NOT NULL AUTO_INCREMENT,
  text VARCHAR(255) NOT NULL,
  PRIMARY KEY (id)
);

INSERT INTO overlays (text) VALUES
  ("TEXT 1"),
  ("TEXT 2"),
  ("TEXT 3"),
  ("TEXT 4"),
  ("TEXT 5"),
  ("TEXT 6"),
  ("TEXT 7"),
  ("TEXT 8"),
  ("TEXT 9");

-- +migrate Down
DROP TABLE IF EXISTS overlays;

