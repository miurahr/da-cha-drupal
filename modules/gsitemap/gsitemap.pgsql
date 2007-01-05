-- Thanks to Joel S. for providing this
CREATE TABLE gsitemap (
  nid integer PRIMARY KEY, 
  last_changed integer, 
  previously_changed integer, 
  last_comment integer, 
  previous_comment integer, 
  priority_override real);
