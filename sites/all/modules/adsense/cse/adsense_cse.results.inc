<?php
// $Id: adsense_cse.results.inc,v 1.1.2.3 2008/09/21 02:46:04 kbahey Exp $

/**
 * @file
 * Displays the page containing the results of the Adsense for Search box
 */

/**
 * Creates the CSE search results page for site-embedded search results
 *
 * @return
 *   JavaScript that embeds the Google results
 */
function _adsense_cse_results() {
  // Log the search keys:
  watchdog('AdSense search', 'Search keywords: ' . urldecode(check_plain($_GET['as_q'])), WATCHDOG_NOTICE);

  // Output search results
  $width   = variable_get('adsense_cse_frame_width', ADSENSE_CSE_FRAME_WIDTH_DEFAULT);
  $country = variable_get('adsense_cse_country', ADSENSE_CSE_COUNTRY_DEFAULT);

  if (variable_get('adsense_test_mode', ADSENSE_TEST_MODE_DEFAULT)) {
    $adtest = '  var googleAdtest = "on";';
  }

  $output = <<<CSE_RESULTS_TXT
<div id="cse-search-results"></div>
<script type="text/javascript">
  var googleSearchIframeName = "cse-search-results";
  var googleSearchFormName = "cse-search-box";
  var googleSearchFrameWidth = $width;
  var googleSearchDomain = "$country";
  var googleSearchPath = "/cse";
$adtest
</script>
<script type="text/javascript" src="http://www.google.com/afsonline/show_afs_search.js"></script>
CSE_RESULTS_TXT;

  // Remove empty lines
  $output = str_replace("\n\n", "\n", $output);

  return $output;
}
