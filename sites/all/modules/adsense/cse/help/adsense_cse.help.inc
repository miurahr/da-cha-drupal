<?php
// $Id: adsense_cse.help.inc,v 1.1.2.3 2008/11/06 15:10:57 kbahey Exp $
// Copyright 2005-2008 Khalid Baheyeldin - http://2bits.com
// Copyright 2008 Joao Ventura - http://www.venturas.org

/**
 * @file
 * Helpfile for the Managed ads generator module
 */

/**
 * Creates the help text for the Managed Ads tab
 *
 * @return
 *   HTML with the help text
 */
function adsense_cse_help_text() {
  $output = <<<EOF
<h2>Overview</h2>
<p>This module enables the simple inclusion of the new form of Google
AdSense for Search in your Drupal site.</p>

<h2>Prerequisites</h2>
<p>You must have a Google AdSense account before using this module.

<h2>Configuration</h2>
<p>To use this module, simply go to
<a href="https://www.google.com/adsense/settings">Google's AdSense site</a>
and create your AdSense for Search ad. The generated code will contain a
field with partner-<em>Publisher ID</em>:<em>Slot Id</em>. If the code
provided is, for example, partner-pub-0123456789:<strong>abcdef-ghij
</strong>, the Slot Id for that ad is <strong>abcdef-ghij</strong>.</p>
EOF;
  return $output;
}