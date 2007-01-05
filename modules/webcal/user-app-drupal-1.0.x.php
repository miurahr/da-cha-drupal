<?php
/* $Id: user-app-drupal-1.0.x.php,v 1.1.4.2 2006/11/27 23:37:38 jaredwiltshire Exp $ */

if ( empty ( $PHP_SELF ) && ! empty ( $_SERVER ) &&
  ! empty ( $_SERVER['PHP_SELF'] ) ) {
  $PHP_SELF = $_SERVER['PHP_SELF'];
}
if ( ! empty ( $PHP_SELF ) && preg_match ( "/\/includes\//", $PHP_SELF ) ) {
    die ( "You can't access this file directly!" );
}

// This file contains all the functions for getting information
// about users from Drupal 5.0

// This plugin file for WebCalendar 1.0.x uses the Drupal user number as
// the login id because Drupal usernames can be changed.
// User administration is done through Drupal.

// The following functions from this file are called by WebCalendar:
// user_logged_in()
// user_get_users()
// user_load_variables()
// app_login_screen()
// user_delete_user()
// user_update_user()
// user_update_user_password()
// user_add_user()

// The following functions are default functions:
// user_delete_user()
// user_update_user()
// user_update_user_password()
// user_add_user()

/************************* Config ***********************************/

// Full URL to Drupal (including http:// or https:// and a trailing slash)
$app_url = 'http://www.yoursite.com/drupal/';

// Is WebCalendar going to be loaded in an iframe?
$app_in_iframe = true;

// Name of database containing Drupal's tables
$app_db = 'drupal';

// Host that Drupal's db is on
$app_host = 'localhost';

// Login/Password to access Drupal's database
$app_login = 'username';
$app_pass  = 'password';

// Drupal's database prefix
$app_db_prefix = '';

/*************************** End Config *****************************/

$app_user_table = $app_db_prefix . 'users';
$app_session_table = $app_db_prefix . 'sessions';
$app_permission_table = $app_db_prefix . 'permission';
$app_users_roles_table = $app_db_prefix . 'users_roles';

/* Add a slash to the end if its not there
if (substr($app_url, -1, 1) != '/') {
  $app_url .= '/';
}
*/

if ($app_in_iframe) {
  $app_login_page = "javascript:parent.document.location='" . $app_url . "user?destination=webcal'";
  $app_logout_page = "javascript:parent.document.location='" . $app_url . "logout'";
}
else {
  $app_login_page = $app_url . "?destination=" . substr($_SERVER['REQUEST_URI'],1);
  $app_logout_page = $app_url . "logout";
}

// Are Drupal's tables in the same database as WebCalendar's?
$app_same_db = (($db_database == $app_db) && ($app_host == $db_host)) ? '1' : '0';

// User administration should be done through Drupal's interface
$user_can_update_password = false;
$admin_can_add_user = false;

// Allow admin to delete user from webcal tables (not from Drupal)
$admin_can_delete_user = true;

// Checks to see if the user is logged into Drupal & has permission
// Returns: login id (i.e. the user id of the logged in Drupal user, if they
// have permission to log into WebCalendar)
function user_logged_in() {
  global $PUBLIC_ACCESS;
  global $app_user_table, $app_session_table;
  global $app_host, $app_login, $app_pass, $app_db, $app_same_db;
  global $c, $db_host, $db_login, $db_password, $db_database;
  
  $sid = $_COOKIE['PHPSESSID'];
  
  if ($app_same_db != '1') $c = dbi_connect($app_host, $app_login, $app_pass, $app_db);
  
  if (!empty($sid)) {
    $sql = "SELECT u.uid FROM $app_session_table s, $app_user_table u WHERE s.sid = '$sid' AND s.uid=u.uid";
    $res = dbi_query($sql);
    if ($res) {
      if ($row = dbi_fetch_row($res)) {
        $uid = $row[0];
      }
      dbi_free_result($res);
    }
    
    //update last access times for sessions and users
    $sql = "UPDATE $app_session_table SET timestamp = '".time()."' WHERE sid = '$sid' ";
    dbi_query ( $sql );
    $sql = "UPDATE $app_user_table u, $app_session_table s SET u.access = '".time()."' WHERE s.sid = '$sid' AND u.uid = s.uid AND s.uid <> 0";
    dbi_query ( $sql );
  }
  
  if (!isset($uid)) {
    $uid = 0;
  }
  
  $login = false;
  
  if (check_permissions($uid, "access webcal") && $PUBLIC_ACCESS == 'Y') {
    $login = '__public__';
  }
  
  if (check_permissions($uid, "login to webcal")) {
    $login = $uid;
  }
  
  if ($app_same_db != '1') $c = dbi_connect($db_host, $db_login, $db_password, $db_database);

/* Prints debug information
  print "<pre>";
  print_r( 'uid='.$uid."\nlogin=".$login."\n");
  global $cached_users;
  print_r ($cached_users);
  print "</pre>";
  exit;
*/
  
  return $login;
}

// Checks a given Drupal user id to see if they have a certain permission
// Precondition: Assumes that the database is already connected
// Returns: true if the user has the permission, false if they dont
function check_permissions($uid, $permission) {
  global $cached_users;
  global $app_permission_table, $app_users_roles_table;
  
  if ($uid == 1) {
    return true;
  }
  
  if (empty ($cached_users[$permission])) {
    $rids = array();
    $res = dbi_query("SELECT rid, perm FROM $app_permission_table");
    if ($res) {
      while ($row = dbi_fetch_row($res)) {
        if (strpos($row[1], $permission) !== FALSE) {
          $rids[] = $row[0];
        }
      }
      dbi_free_result ( $res );
    }
    
    $cached_users[$permission] = array ();
    
    //echo "role ids for '$permission'= ";
    //print_r ($rids);
    
    // check if anonymous users or all authenticated users have the permission
    if (in_array(1, $rids) || (in_array(2, $rids) && $uid != 0)) {
      $cached_users[$permission][] = "*";
    }
    else {
      // Get all the user ids that have the permission and add them to the cached users array
      $rid_string = implode(',', $rids);
      if ($rid_string) {
        $res = dbi_query("SELECT uid FROM $app_users_roles_table WHERE rid IN ($rid_string)");
        if ($res) {
          while ($row = dbi_fetch_row($res)) {
            $cached_users[$permission][] = $row[0];
          }
          dbi_free_result ( $res );
        }
      }
    }
  }
  
  foreach ($cached_users[$permission] as $certain_user) {
    if ($certain_user == $uid || $certain_user == "*")
      return true;
  }
  
  return false;
}

// Gets a list of Drupal users with permission to login to WebCalendar
// Returns: An array containing information about all Drupal users who have
// permission to login to WebCalendar
function user_get_users () {
  global $PUBLIC_ACCESS, $PUBLIC_ACCESS_FULLNAME, $app_user_table, $app_session_table;
  global $app_host, $app_login, $app_pass, $app_db, $app_same_db;
  global $c, $db_host, $db_login, $db_password, $db_database;

  $count = 0;
  $ret = array ();
  
  if ( $PUBLIC_ACCESS == 'Y' )
    $ret[$count++] = array (
       'cal_login' => '__public__',
       'cal_lastname' => '',
       'cal_firstname' => '',
       'cal_is_admin' => 'N',
       'cal_email' => '',
       'cal_password' => '',
       'cal_fullname' => $PUBLIC_ACCESS_FULLNAME
    );
  
  // if application is in a separate db, we have to connect to it
  if ($app_same_db != '1') $c = dbi_connect($app_host, $app_login, $app_pass, $app_db);
  
  $sql = "SELECT uid, name, mail FROM $app_user_table WHERE uid <> '0' ORDER BY uid";
  $res = dbi_query ( $sql );
  if ( $res ) {
    while ( $row = dbi_fetch_row ( $res ) ) {
      list($fname, $lname) = split (" ",$row[1]);
      if (check_permissions($row[0], 'login to webcal')) {
        $ret[$count++] = array (
          "cal_login" => $row[0],
          "cal_lastname" => $lname,
          "cal_firstname" => $fname,
          "cal_is_admin" => check_permissions($row[0], 'webcal admin'),
          "cal_email" => $row[2],
          "cal_fullname" => $row[1]
        );
      }
    }
    dbi_free_result ( $res );
  }
  
  // if application is in a separate db, we have to connect back to the webcal db
  if ($app_same_db != '1') $c = dbi_connect($db_host, $db_login, $db_password, $db_database);
  
  return $ret;
}

// Load info about a user (first name, last name, admin) and set globally.
// params:
//   $user - user login
//   $prefix - variable prefix to use
// Returns: true if no errors occured, false if db errors occured
function user_load_variables ($login, $prefix) {
  global $PUBLIC_ACCESS_FULLNAME, $NONUSER_PREFIX;
  global $app_host, $app_login, $app_pass, $app_db, $app_user_table;
  global $c, $db_host, $db_login, $db_password, $db_database, $app_same_db;
  
  if ($NONUSER_PREFIX && substr($login, 0, strlen($NONUSER_PREFIX)) == $NONUSER_PREFIX) {
    nonuser_load_variables ($login, $prefix);
    return true;
  }
  
  if ( $login == '__public__' ) {
    $GLOBALS[$prefix . 'login'] = $login;
    $GLOBALS[$prefix . 'firstname'] = '';
    $GLOBALS[$prefix . 'lastname'] = '';
    $GLOBALS[$prefix . 'is_admin'] = 'N';
    $GLOBALS[$prefix . 'email'] = '';
    $GLOBALS[$prefix . 'fullname'] = $PUBLIC_ACCESS_FULLNAME;
    $GLOBALS[$prefix . 'password'] = '';
    return true;
  }

  // if application is in a separate db, we have to connect to it
  if ($app_same_db != '1') $c = dbi_connect($app_host, $app_login, $app_pass, $app_db);
  
  $res = dbi_query ("SELECT uid, name, mail FROM $app_user_table WHERE uid = $login");
  if ($res) {
    if ($row = dbi_fetch_row($res)) {
      list($fname, $lname) = split (" ",$row[1]);
      $GLOBALS[$prefix . 'login'] = $login;
      $GLOBALS[$prefix . 'firstname'] = $fname;
      $GLOBALS[$prefix . 'lastname'] = $lname;
      $GLOBALS[$prefix . 'is_admin'] = check_permissions($row[0], 'webcal admin');
      $GLOBALS[$prefix . 'email'] = $row[2];
      $GLOBALS[$prefix . 'fullname'] = $row[1];
    }
    dbi_free_result($res);
  } else {
    $error = db_error();
    return false;
  }
  
  // if application is in a separate db, we have to connect back to the webcal db
  if ($app_same_db != '1') $c = dbi_connect($db_host, $db_login, $db_password, $db_database);

  return true;
}

// Redirect the user to the application's login screen
function app_login_screen($return = '') {
  global $app_url, $app_in_iframe;
  
  if (empty($return) && $app_in_iframe) {
    $return = "webcal";
  }
  if (!empty($return)) {
    $return = "?destination=$return";
  }
  
  $login_page = $app_url . "user" . $return;
  
  if ($app_in_iframe) {
    echo "<html><body onload=\"parent.document.location='$login_page'\"></body></html>";
    exit;
  }
  
  header("Location: $login_page");
  exit;
}

/********************************************************************* 
 *
 *      Functions that are unchanged from other user-app files
 *
 ********************************************************************/

// Delete a user from the webcalendar tables. (NOT from the application)
// We assume that we've already checked to make sure this user doesn't
// have events still in the database.
// params:
//   $user - user to delete
function user_delete_user ( $user ) {
  // Get event ids for all events this user is a participant
  $events = array ();
  $res = dbi_query ( "SELECT webcal_entry.cal_id " .
    "FROM webcal_entry, webcal_entry_user " .
    "WHERE webcal_entry.cal_id = webcal_entry_user.cal_id " .
    "AND webcal_entry_user.cal_login = '$user'" );
  if ( $res ) {
    while ( $row = dbi_fetch_row ( $res ) ) {
      $events[] = $row[0];
    }
  }

  // Now count number of participants in each event...
  // If just 1, then save id to be deleted
  $delete_em = array ();
  for ( $i = 0; $i < count ( $events ); $i++ ) {
    $res = dbi_query ( "SELECT COUNT(*) FROM webcal_entry_user " .
      "WHERE cal_id = " . $events[$i] );
    if ( $res ) {
      if ( $row = dbi_fetch_row ( $res ) ) {
        if ( $row[0] == 1 )
    $delete_em[] = $events[$i];
      }
      dbi_free_result ( $res );
    }
  }
  // Now delete events that were just for this user
  for ( $i = 0; $i < count ( $delete_em ); $i++ ) {
    dbi_query ( "DELETE FROM webcal_entry WHERE cal_id = " . $delete_em[$i] );
  }

  // Delete user participation from events
  dbi_query ( "DELETE FROM webcal_entry_user WHERE cal_login = '$user'" );

  // Delete preferences
  dbi_query ( "DELETE FROM webcal_user_pref WHERE cal_login = '$user'" );

  // Delete from groups
  dbi_query ( "DELETE FROM webcal_group_user WHERE cal_login = '$user'" );

  // Delete bosses & assistants
  dbi_query ( "DELETE FROM webcal_asst WHERE cal_boss = '$user'" );
  dbi_query ( "DELETE FROM webcal_asst WHERE cal_assistant = '$user'" );

  // Delete user's views
  $delete_em = array ();
  $res = dbi_query ( "SELECT cal_view_id FROM webcal_view " .
    "WHERE cal_owner = '$user'" );
  if ( $res ) {
    while ( $row = dbi_fetch_row ( $res ) ) {
      $delete_em[] = $row[0];
    }
    dbi_free_result ( $res );
  }
  for ( $i = 0; $i < count ( $delete_em ); $i++ ) {
    dbi_query ( "DELETE FROM webcal_view_user WHERE cal_view_id = " .
      $delete_em[$i] );
  }
  dbi_query ( "DELETE FROM webcal_view WHERE cal_owner = '$user'" );

  // Delete layers
  dbi_query ( "DELETE FROM webcal_user_layers WHERE cal_login = '$user'" );

  // Delete any layers other users may have that point to this user.
  dbi_query ( "DELETE FROM webcal_user_layers WHERE cal_layeruser = '$user'" );
}

// Functions we don't use with this file:
function user_update_user ( $user, $firstname, $lastname, $email, $admin ) {
  global $error;
  $error = 'User admin not supported.'; return false;
}
function user_update_user_password ( $user, $password ) {
  global $error;
  $error = 'User admin not supported.'; return false;
}
function user_add_user ( $user, $password, $firstname, $lastname, $email, $admin ) {
  global $error;
  $error = 'User admin not supported.'; return false;
}
?>
