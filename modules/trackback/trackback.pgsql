CREATE TABLE trackback_received (
nid integer NOT NULL,
trid integer NOT NULL,
created integer NOT NULL,
site varchar(255) NOT NULL,
name varchar(60) NOT NULL,
subject varchar(64) NOT NULL,
url varchar(255) NOT NULL,
excerpt varchar(255) NOT NULL,
status smallint default '0',
PRIMARY KEY (trid)
);

CREATE TABLE trackback_sent (
nid integer NOT NULL,
url varchar(255) NOT NULL default '',
successful smallint NOT NULL,
PRIMARY KEY (nid, url)
);

CREATE TABLE trackback_node (
nid integer NOT NULL,
awaiting_cron smallint NOT NULL,
can_receive smallint NOT NULL,
PRIMARY KEY (nid)
);
