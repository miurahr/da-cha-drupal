<?php
// $Id: template.php,v 1.10.2.4 2008/06/26 18:38:16 hswong3i Exp $

function internet_services_theme() {
  return array(
    'primary' => array(
      'arguments' => array('form' => NULL, 'items' => NULL),
    ),
    'mission' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Return a themed primary menu.
 */
function internet_services_primary($items = array()) {
  $menu_options = menu_get_menus();
  $primary_links = variable_get('menu_primary_links_source', 'primary-links');
  $output = '<div class="title">' . $menu_options[$primary_links] . '</div>';
  $output .= theme('links', $items);
  return $output;
}

/**
 * Return a themed mission trail.
 *
 * @return
 *   a string containing the mission output, or execute PHP code snippet if
 *   mission is enclosed with <?php ?>.
 */
function internet_services_mission() {
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
