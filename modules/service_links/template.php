<?php
// $Id: template.php,v 1.1.2.2 2006/08/24 07:19:25 frjo Exp $

/**
 * @file
 * Example template.php for service_links.module
 * Use <?php print $service_links ?> to insert links in your node.tpl.php file.
 */

function _phptemplate_variables($hook, $vars) {
  switch($hook) {
    case 'node':
      if (module_exist('service_links')) {
        $vars['service_links'] = theme('links', service_links_render($vars['node']));
      }
      break;
  }

  return $vars;
}
?>
