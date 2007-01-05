<?php

$access_check = TRUE;

include_once "includes/bootstrap.inc";
include_once "includes/common.inc";

// Define the various updates in an array("date : comment" => "function");
$sql_updates = array(
  'Trackback update for Drupal 4.5 --> Drupal 4.6' => 'trackback_update_1'
);

if (!ini_get("safe_mode")) {
  set_time_limit(180);
}

function trackback_update_sql($sql) {
  $edit = $_POST["edit"];
  $result = db_query($sql);
  if ($result) {
    return array('1', nl2br(htmlentities($sql)) ." ", "<div style=\"color: green;\">OK</div>\n");
  }
  else {
    return array('0', nl2br(htmlentities($sql)) ." ", "<div style=\"color: red;\">FAILED</div>\n");
  }
}

function trackback_update_1() {
  // trackback updates
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD trid int(10) unsigned NOT NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD created int(11) NOT NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD site varchar(255) NOT NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD name varchar(60) default NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD subject varchar(64) NOT NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD excerpt varchar(255) NOT NULL');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD status tinyint(1) unsigned default \'0\'');

  $ret[] = trackback_update_sql("CREATE TABLE {trackback_node} (
    nid int(10) unsigned NOT NULL,
    awaiting_cron tinyint(1) NOT NULL,
    can_receive tinyint(1) NOT NULL,
    PRIMARY KEY (nid)
    )");

  $result = db_query('SELECT tr.nid, tr.cid, c.timestamp, c.homepage, c.name, c.subject, c.comment FROM {trackback_received} tr LEFT JOIN {comments} c ON tr.cid = c.cid');
  while ($trackback = db_fetch_object($result)) {
    $trid = db_next_id('{trackback_received}_trid');
    db_query("UPDATE {trackback_received} SET trid = %d, created = %d, site = '%s', name = '%s', subject = '%s', excerpt = '%s' WHERE nid = %d AND cid = %d", $trid, $trackback->timestamp, $trackback->homepage, $trackback->name, $trackback->subject, $trackback->comment, $trackback->nid, $trackback->cid);
    _comment_delete_thread($trackback);
    _comment_update_node_statistics($trackback->nid);
  }

  trackback_update_sql('UPDATE {trackback_received} SET status = 1');
  
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} DROP PRIMARY KEY');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} DROP cid');
  $ret[] = trackback_update_sql('ALTER TABLE {trackback_received} ADD PRIMARY KEY (trid)');
    
  $ret[] = trackback_update_sql("CREATE TABLE {spam_trackbacks} (
    trid int(10) unsigned NOT NULL default '0',
    rating int(2) unsigned default '0',
    spam tinyint(1) unsigned default '0',
    last int(11) unsigned default '0',
    PRIMARY KEY trid (trid),
    KEY rating (rating),
    KEY spam (spam),
    KEY last (last)
  );");

  return $ret;
}

function trackback_upgrade_page_header($title) {
  $output = "<html><head><title>$title</title>";
  $output .= <<<EOF
      <link rel="stylesheet" type="text/css" media="print" href="misc/print.css" />
      <style type="text/css" title="layout" media="Screen">
        @import url("misc/drupal.css");
      </style>
EOF;
  $output .= "</head><body>";
  $output .= "<div id=\"logo\"><a href=\"http://drupal.org/\"><img src=\"misc/druplicon-small.png\" alt=\"Druplicon - Drupal logo\" title=\"Druplicon - Drupal logo\" /></a></div>";
  $output .= "<div id=\"update\"><h1>$title</h1>";
  return $output;
}

function trackback_upgrade_page_footer() {
  return "</div></body></html>";
}

function trackback_upgrade_access_denied_page() {
  $output  = trackback_upgrade_page_header("Access denied");
  $output .= "Access denied.  You are not authorized to access to this page.  Please log in as the user with user ID #1. If you cannot log-in, you will have to edit <code>modules/trackback/trackback_upgrade.php</code> to by-pass this access check; in that case, open <code>modules/trackback/trackback_upgrade.php</code> in a text editor and follow the instructions at the top.";
  $output .= trackback_upgrade_page_footer();
  return $output;
}

function trackback_upgrade_info() {
  $output .= "<ul>\n";
  $output .= "<li>Use this script to <strong>fix and update permissions you've set with trackback</strong>.  You don't need this script when installing the trackback.module from scratch.</li>"."\n";
  $output .= "<li>In versions of trackback prior to 4.6, there was an issue with users not being able to find and see in listing the nodes that they didn't have permissions to see, but still being able to go directly to the URL of an off-limits node and view it.  This database upgrade is a way of correcting that problem.</li>"."\n";
  $output .= "</ul>"."\n";
  return $output;
}


function trackback_update_data() {
  global $sql_updates;
  $output = '';
  $output .= "\n<pre>\n";
  $ret = trackback_update_1();
  foreach ($ret as $return) {
    $output .= $return[1];
    $output .= $return[2];
  }
  $output .= "</pre>\n";
  return $output;
}


function trackback_upgrade_page() {
  global $user;

  if (isset($_POST['op'])) {
    $op = $_POST['op'];
  }

  switch ($op) {
    case "Update":
      // make sure we have updates to run.
      print trackback_upgrade_page_header("trackback.module database update");
      $links[] = "<a href=\"index.php\">main page</a>";
      $links[] = "<a href=\"index.php?q=admin\">administration pages</a>";
      print theme("item_list", $links);
      
      print trackback_update_data();
      
      print trackback_upgrade_page_footer();
      break;
    default:
      // make update form and output it.
      $form = form_submit('Update');
      $form = form($form);
      print trackback_upgrade_page_header('trackback.module database update');
      print trackback_upgrade_info();
      print $form;
      print trackback_upgrade_page_footer();
      break;
  }
}

if ((!$access_check) || $user->uid == 1) {
  print trackback_upgrade_page();
}  
else {
  print trackback_upgrade_page_header("Access denied");
  print "Access denied.  You are not authorized to access to this page.  Please log in as the user with user ID #1. If you cannot log-in, you will have to edit <code>modules/trackback/trackback_upgrade.php</code> to by-pass this access check; in that case, open <code>modules/trackback/trackback_upgrade.php</code> in a text editor and follow the instructions at the top.";
  print trackback_upgrade_page_footer();
}


?>
