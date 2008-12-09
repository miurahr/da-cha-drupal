<?php
// $Id: template.php,v 1.13.2.1 2008/05/06 06:46:42 hswong3i Exp $

function contented7_theme() {
  return array(
    'mission' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Return a themed mission trail.
 *
 * @return
 *   a string containing the mission output, or execute PHP code snippet if
 *   mission is enclosed with <?php ?>.
 */
function contented7_mission() {
  $mission = theme_get_setting('mission');
  if (preg_match('/^<\?php/', $mission)) {
    $mission = drupal_eval($mission);
  }
  else {
    $mission = filter_xss_admin($mission);
  }
  return isset($mission) ? $mission : '';
}

/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
  global $language;

  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/fix-ie.css" />';
  if (defined('LANGUAGE_RTL') && $language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}
