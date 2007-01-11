<?php

function phptemplate_block_list($region) {
  //  This is the list function from the block module.  We have to comment
  // out the throttle test, which for some reason breaks node previews.
  // As a result, if blocks are throttled, we may get the wrong layout.
  global $user, $theme_key;

  static $blocks = array();

  if (!count($blocks)) {
    $result = db_query("SELECT * FROM {blocks} WHERE theme = '%s' AND status = 1 ORDER BY region, weight, module", $theme_key);
    while ($block = db_fetch_object($result)) {
      if (!isset($blocks[$block->region])) {
        $blocks[$block->region] = array();
      }
      // Use the user's block visibility setting, if necessary
      if ($block->custom != 0) {
        if ($user->uid && isset($user->block[$block->module][$block->delta])) {
          $enabled = $user->block[$block->module][$block->delta];
        }
        else {
          $enabled = ($block->custom == 1);
        }
      }
      else {
        $enabled = TRUE;
      }

      // Match path if necessary
      if ($block->pages) {
        if ($block->visibility < 2) {
          $path = drupal_get_path_alias($_GET['q']);
          $regexp = '/^('. preg_replace(array('/(\r\n?|\n)/', '/\\\\\*/', '/(^|\|)\\\\<front\\\\>($|\|)/'), array('|', '.*', '\1'. preg_quote(variable_get('site_frontpage', 'node'), '/') .'\2'), preg_quote($block->pages, '/')) .')$/';
          $page_match = !($block->visibility xor preg_match($regexp, $path));
        }
        else {
          $page_match = drupal_eval($block->pages);
        }
      }
      else {
         $page_match = TRUE;
      }

      if ($enabled && $page_match) {
        // Check the current throttle status and see if block should be displayed
        // based on server load.
//         if (!($block->throttle && (module_invoke('throttle', 'status') > 0))) {
//           $array = module_invoke($block->module, 'block', 'view', $block->delta);
//           if (isset($array) && is_array($array)) {
//             foreach ($array as $k => $v) {
//               $block->$k = $v;
//             }
//           }
//         }
        if (isset($block->content) && $block->content) {
          $blocks[$block->region]["{$block->module}_{$block->delta}"] = $block;
        }
      }
    }
  }
  // Create an empty array if there were no entries
  if (!isset($blocks[$region])) {
    //    $blocks[$region] = array();
    return 0;
  }

  return 1;//$blocks[$region];
}

function _phptemplate_variables($hook, $vars) {
  // Detect whether left and right sidebars are used, and
  // set layoutcode accordingly
  $vars['layoutcode'] = '3';  // default - right
  if ($left=phptemplate_block_list("left")) {
    $vars['layoutcode'] = '2'; }   // left
  if ($left && phptemplate_block_list("right")) {
    $vars['layoutcode'] = '1'; } //both
  return $vars;
}



function phptemplate_menu_tree($pid=1) {
  // Code adapted from the nice_menus module
  // generates nested <ul> <li> lists
  $menu = menu_get_menu($pid); 
  $output = ''; 
  if ($menu['visible'][$pid]['children']) {
    foreach ($menu['visible'][$pid]['children'] as $mid) {
      if (count($menu['visible'][$mid]['children']) > 0) {
	$output.= "<li>".menu_item_link($mid);
	if (menu_in_active_trail($mid)) { // only output children if they should be seen
	  $output.= "<ul>";
	  $tmp = phptemplate_menu_tree($mid);
	  $output.= $tmp;
	  $output.= "</ul>";
	}
	$output.= "</li>";
      } 
      else {
	$output.= "<li>".menu_item_link($mid)."</li>";
      }
    }
  }
  return $output;
}
