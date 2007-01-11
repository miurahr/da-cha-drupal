<?php

function leech_news_parse_news_feed(&$xml) {
  // Some feeds already use CDATA but in "wrong way": http://www.rocketboom.com/vlog/quicktime_daily_enclosures.xml (ie. <description> something <CDATA soemthing else></description>
  $data = trim(str_replace(array('<![CDATA[', ']]>'), '', $xml));
  
  // Add CDATA around content which may contain (x)html data, and is not contained in CDATA yet
  $src = array(
    '%(<(link|content|content:encoded|description|title|summary|info|tagline|copyright|source|itunes:summary|media:text|text)(?>[^<]*(?<!/)>)(?!<!\[CDATA\[))(.*)(</\2>)%sUS',
    '%24:(\d\d:\d\d)%' // workaround buggy hour format in feeds
    /*'%(<(\w+)(?>[^<]*type=")(?:text/html|application/xhtml\+xml|html|xhtml")(?>[^<]*(?<!/)>)(?!<!\[CDATA\[))(.*)(</\2>)%sUS'*/
    );
  $dst = array(
    '$1<![CDATA[$3]]>$4',
    '00:$1'
    );
  $data = preg_replace($src, $dst, $data);

  $xml_parser = new LeechNewsParser();
  $xml_tree = $xml_parser->Parse($data);
  return _leech_news_get_feed($xml_tree);
}


function _leech_news_get_feed(&$xml_tree) {
  $feed = new StdClass();

  if ($xml_tree['RSS']) { // RSS 0.91, 0.92, 2.0
    $feed->format = 'RSS';
    $feed->root = &$xml_tree['RSS'][0];
    $feed->channel = &$xml_tree['RSS'][0]['CHANNEL'][0];
    $items = &$xml_tree['RSS'][0]['CHANNEL'][0]['ITEM'];

    $feed->logo = $feed->channel['IMAGE'][0];
    $feed->link = $feed->channel['LINK'][0]['VALUE'];
    $feed->description = $feed->channel['DESCRIPTION'][0]['VALUE'];

    if ($feed->items[0]['GUID'][0]['VALUE']) {
      $feed->has_guids = 'GUID';
    }
  }
  else if ($xml_tree['RDF:RDF']) {
    $feed->format = 'RDF';
    $feed->root = &$xml_tree['RDF:RDF'][0];
    $feed->channel = &$xml_tree['RDF:RDF'][0]['CHANNEL'][0];
    $items = &$xml_tree['RDF:RDF'][0]['ITEM'];

    $feed->logo = $feed->root['IMAGE'][0];
    $feed->link = $feed->channel['LINK'][0]['VALUE'];
    $feed->description = $feed->channel['DESCRIPTION'][0]['VALUE'];

    if ($feed->items[0]['GUID'][0]['VALUE']) {
      $feed->has_guids = 'GUID';
    }
  }
  else if ($xml_tree['FEED']) { // Atom 0.3, 1.0
    $feed->format = 'ATOM';
    $feed->root = &$xml_tree['FEED'][0];
    $feed->channel = &$xml_tree['FEED'][0];
    $items = &$xml_tree['FEED'][0]['ENTRY'];

    $feed->logo = ($feed->channel['LOGO'][0]['VALUE'] ? $feed->channel['LOGO'][0]['VALUE'] : $feed->channel['ICON'][0]['VALUE']);
    // TODO: remove this Atom hack when we have field mapping or at least specialized parsers in place
      if (count($feed->channel['LINK']) > 1) {
        $feed->link = '';
        foreach ($feed->channel['LINK'] as $l) {
          if ($l['REL'] == 'alternate') {
            $feed->link = $l['HREF'];
          }
        }
      }
      else {
        $feed->link = $feed->channel['LINK'][0]['HREF'];
      }
    $feed->description = $feed->channel['TAGLINE'][0]['VALUE'];

    if ($feed->items[0]['ATOM:ID'][0]['VALUE']) {
      $feed->has_guids = 'ATOM:ID';
    }
    else if ($feed->items[0]['ID'][0]['VALUE']) {
      $feed->has_guids = 'ID';
    }
  }
  else if ($xml_tree['CHANNEL']) { // RSS 1.1
    $feed->format = 'RSS';
    $feed->root = &$xml_tree['CHANNEL'][0];
    $feed->channel = &$xml_tree['CHANNEL'][0];
    $items = &$xml_tree['CHANNEL'][0]['ITEMS'][0]['ITEM'];

    $feed->logo = $feed->channel['IMAGE'][0];
    $feed->link = $feed->channel['LINK'][0]['VALUE'];
    $feed->description = $feed->channel['DESCRIPTION'][0]['VALUE'];

    if ($feed->items[0]['GUID'][0]['VALUE']) {
      $feed->has_guids = 'GUID';
    }
  }
  else {
    // unsupported format
    $feed->format = '[unknown]';
    $feed->root = array();
    $feed->channel = array();
    $items = array();

    $feed->logo = '';
    $feed->link = '';
    $feed->description = '';

    $feed->has_guids = FALSE;
    return $feed;
  }

  // Now handle image/logo tags which are parents of other tags with url and stuff
  if (is_array($feed->logo)) {
    if ($feed->logo['URL']) {
      $feed->logo = $feed->logo['URL'][0]['VALUE'];
    }
    else {
      // unsupported
      $feed->logo = '';
    }
  }

  // Try to find author of feed
  if ($feed->channel['AUTHOR'][0]['VALUE']) {
    $feed->author = $channel['AUTHOR'][0]['VALUE'];
  }
  if ($feed->channel['AUTHOR'][0]['NAME'][0]['VALUE']) {
    $feed->author = $feed->channel['AUTHOR'][0]['NAME'][0]['VALUE'];
  }
  else if ($feed->channel['DC:CREATOR']) {
    $feed->author = $feed->channel['DC:CREATOR'][0]['VALUE'];
  }
  else {
    $feed->author = '';
  }

  // TODO: find nicer way for handling namespaces ;)
  if ($items[0]['PUBDATE']) $feed->has_dates = 'PUBDATE';                        // RSS 2.0
  else if ($items[0]['DC:DATE']) $feed->has_dates = 'DC:DATE';                   // Dublin core
  else if ($items[0]['DATE']) $feed->has_dates = 'DATE';                         // Dublin core
  else if ($items[0]['DCTERMS:ISSUED']) $feed->has_dates = 'DCTERMS:ISSUED';     // Dublin core
  else if ($items[0]['ISSUED']) $feed->has_dates = 'ISSUED';                     // Dublin core
  else if ($items[0]['DCTERMS:CREATED']) $feed->has_dates = 'DCTERMS:CREATED';   // Dublin core
  else if ($items[0]['CREATED']) $feed->has_dates = 'CREATED';                   // Dublin core
  else if ($items[0]['DCTERMS:MODIFIED']) $feed->has_dates = 'DCTERMS:MODIFIED'; // Dublin core
  else if ($items[0]['MODIFIED']) $feed->has_dates = 'MODIFIED';                 // Dublin core
  else if ($items[0]['ATOM:UPDATED']) $feed->has_dates = 'ATOM:UPDATED';         // Atom
  else if ($items[0]['UPDATED']) $feed->has_dates = 'UPDATED';                   // Atom
  else $feed->has_dates = NULL;

  // Set default value
  $feed->has_unique_links = TRUE;
  $feed->items = array();
  $temp = array();
  for ($index = count($items) - 1; $index >= 0; $index--) {
    $feed->items[] = _leech_news_get_item($items[$index], $feed);

    // If there was no guid try to use link as guid.
    if (!$feed->has_guids && is_array($temp)) {
      $link = &$feed->items[count($feed->items)-1]->link;
      // Check if link is unique
      if (!isset($temp[$link])) {
        $temp[$link] = 1;
      }
      else {
        $feed->has_unique_links = FALSE;
        unset($temp);
      }
    }
  }

  return $feed;
}

function _leech_news_get_item(&$data, &$feed) {
  $item = new StdClass();

  // Description field is needed early for case when no title is specified
  if ($data['DESCRIPTION']) { // RSS 0.91, 0.92, 1.0, 1.1, 2.0
    $item->body = $data['DESCRIPTION'][0]['VALUE'];
  }
  else if ($data['SUMMARY']) { // Atom 0.3, 1.0
    $item->body = $data['SUMMARY'][0]['VALUE'];
  }

  $temp = '';
  if ($data['CONTENT']) { // Atom 0.3, 1.0
    $temp = &$data['CONTENT'][0]['VALUE'];
  }
  else if ($data['CONTENT:ENCODED']) { // Don't know where it came from but it can be found in RSS 2.0 feeds
    $temp = &$data['CONTENT:ENCODED'][0]['VALUE'];
  }
  if (strlen($item->body) < strlen($temp)) {
    if ($item->body) {
      $item->teaser = $item->body;
    }
    $item->body = $temp;
  }

  /*
  ** Resolve the item's title. If no title is found, we use
  ** up to 40 characters of the description ending at a word
  ** boundary but not splitting potential entities.
  */
  if (!($item->title = $data['TITLE'][0]['VALUE'])) {
    $item->title = preg_replace('/^(.*)[^\w;&].*?$/', "\\1", truncate_utf8($item->body, 40));
  }

  // If title was "escaped" then it may still contain entities, becuase each & from entity was also escaped to &amp; before
  // TODO: the same for content?
  if ($data['TITLE'][0]['MODE'] == 'escaped') {
    $item->title = parse_entities($item->title);
  }
  $item->title = strip_tags($item->title);

  /*
  ** Resolve the items link.
  */
  if ($data['LINK']) {
    // TODO: remove this Atom hack when we have field mapping or at least specialized parsers in place
    if (count($data['LINK']) > 1) {
      $item->link = $feed->link;
      foreach ($data['LINK'] as $temp) {
        if ($temp['REL'] == 'alternate') {
          $item->link = $temp['HREF'];
        }
      }
    }
    else {
      $item->link = ($data['LINK'][0]['HREF'] ? $data['LINK'][0]['HREF'] : $data['LINK'][0]['VALUE']);
    }
  }
  elseif ($data['GUID'] && (strncmp($data['GUID'][0]['VALUE'], 'http://', 7) == 0) && $data['GUID'][0]['ISPERMALINK'] != 'false') {
    $item->link = $data['GUID'][0]['VALUE'];
  }
  else {
    $item->link = $feed->link;
  }

  // Try to "sniff" real link from feeds like news.google.com which "hide" real link behind own url
  if (strpos($item->link, 'http://news.google.com/news/url?') === 0) {
    if (preg_match('/\&url=(.*)\&/U', $item->link, $matches) && $matches[1]) {
      $item->link = rawurldecode($matches[1]);
    }
  }
  else if (preg_match('/^\w+:\/\/(?:\w+\.|\.)*yahoo.com\/dailynews\/rss\/.*\*(.*)/', $item->link, $matches)) {
    $item->link = rawurldecode($matches[1]);
  }

  /*
  ** Resolve the items source.
  */
  // RSS 2.0 description of SOURCE is a bit different from ATOM and DC.
  // It says link should point to XML data of source (so i guess to feed/channel??),
  // while ATOM and DC say it just points to original data (and from examples on web
  // it looks like it means link to original article on site, not in RSS/ATOM format).
  if ($data['SOURCE'][0]['VALUE'] && $data['SOURCE'][0]['URL']) { // RSS 2.0
    $item->source_title = $data['SOURCE'][0]['VALUE'];
    $item->source_xml = $data['SOURCE'][0]['URL'];
  }
  if ($data['DC:SOURCE'][0]['VALUE'] || (!$item->source_xml && $data['SOURCE'][0]['VALUE'])) { // Dublin core
    $item->source_link = $data['DC:SOURCE'][0]['VALUE'];
  }
  else if ($data['SOURCE'] || $data['ATOM:SOURCE']) { // ATOM 1.0
    if ($data['SOURCE'][0]['TITLE']) $item->source_title = $data['SOURCE'][0]['TITLE'][0]['VALUE'];
    else if ($data['SOURCE'][0]['ATOM:TITLE']) $item->source_title = $data['SOURCE'][0]['ATOM:TITLE'][0]['VALUE'];
    if ($data['SOURCE'][0]['LINK']) $item->source_link = $data['SOURCE'][0]['LINK'][0]['VALUE'];
    else if ($data['SOURCE'][0]['ATOM:LINK']) $item->source_link = $data['SOURCE'][0]['ATOM:LINK'][0]['VALUE'];
  }

  if (!$item->source_title) {
    $item->source_title = '';
  }
  if (!$item->source_link) {
    $item->source_link = '';
  }
  if (!$item->source_xml) {
    $item->source_xml = '';
  }

  if ($feed->has_dates) {
    $item->date = strtotime($data[$feed->has_dates][0]['VALUE']); // strtotime() returns -1 on failure
    if ($item->date < 0) {
      $item->date = parse_w3cdtf($data[$feed->has_dates][0]['VALUE']); // also returns -1 on failure
      if ($item->date < 0) {
        $item->date = time(); // better than nothing
      }
    }
  }
  else {
    $item->date = time();
  }

  // Try to use RSS:GUID/ATOM:ID as unique identifier
  if ($data['GUID'][0]['VALUE']) { // RSS 2.0
    $item->guid = $data['GUID'][0]['VALUE'];
  }
  else if ($data['ATOM:ID'][0]['VALUE']) { // ATOM 0.3, 1.0
    $item->guid = $data['ATOM:ID'][0]['VALUE'];
  }
  else if ($data['ID'][0]['VALUE']) { // ATOM 0.3, 1.0
    $item->guid = $data['ID'][0]['VALUE'];
  }
  else {
    $feed->has_guids = FALSE;
  }
  // TODO: is there anyway to check if DC:IDENTIFIER is unique?
  //       http://dublincore.org/documents/usageguide/elements.shtml says it can be non-unique so useles for us :(

  // Make relative URLs to be global
  $base = '';
  if ($item->link) {
    $q = strpos($item->link, '?');
    if ($q > 0) {
      $q = strrpos(substr($item->link, 0, $q), '/');
    }
    else {
      $q = strrpos($item->link, '/');
    }
    $base = substr($item->link, 0, $q);
  }
  $item->body = parse_relative_urls($item->body, $base);
  $item->teaser = parse_relative_urls($item->teaser, $base);

  return $item;
}

/**
 * Private function;
 * Parse the W3C date/time format, a subset of ISO 8601. PHP date parsing
 * functions do not handle this format.
 * See http://www.w3.org/TR/NOTE-datetime for more information.
 * Origionally from MagpieRSS (http://magpierss.sourceforge.net/).
 *
 * @param $date_str A string with a potentially W3C DTF date.
 * @return A timestamp if parsed successfully or -1 if not.
 */
function parse_w3cdtf($date_str) {
  if (preg_match('/(\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2})(:(\d{2}))?(?:([-+])(\d{2}):?(\d{2})|(Z))?/', $date_str, $match)) {
    list($year, $month, $day, $hours, $minutes, $seconds) = array($match[1], $match[2], $match[3], $match[4], $match[5], $match[6]);
    // calc epoch for current date assuming GMT
    $epoch = gmmktime($hours, $minutes, $seconds, $month, $day, $year);
    if ($match[10] != 'Z') { // Z is zulu time, aka GMT
      list($tz_mod, $tz_hour, $tz_min) = array($match[8], $match[9], $match[10]);
      // zero out the variables
      if (!$tz_hour) {
        $tz_hour = 0;
      }
      if (!$tz_min) {
        $tz_min = 0;
      }
      $offset_secs = (($tz_hour * 60) + $tz_min) * 60;
      // is timezone ahead of GMT?  then subtract offset
      if ($tz_mod == '+') {
        $offset_secs *= -1;
      }
      $epoch += $offset_secs;
    }
    return $epoch;
  }
  else {
    return -1;
  }
}

/**
 * Private function;
 * from: http://pl2.php.net/manual/en/function.html-entity-decode.php#51055
 * Used as callback function for preg_replace_all() to decode numeric entities to UTF-8 chars
 *
 * @param $ord Number
 * @return UTF-8 string
 */
function _parse_num_entity($ord) {
  $ord = $ord[1];
  if (preg_match('/^x([0-9a-f]+)$/i', $ord, $match)) {
    $ord = hexdec($match[1]);
  }
  else {
    $ord = intval($ord);
  }

  $no_bytes = 0;
  $byte = array();

  if ($ord == 128) {
    return chr(226).chr(130).chr(172);
  }
  else if($ord == 129) {
    return chr(239).chr(191).chr(189);
  }
  else if($ord == 130) {
    return chr(226).chr(128).chr(154);
  }
  else if($ord == 131) {
    return chr(198).chr(146);
  }
  else if($ord == 132) {
    return chr(226).chr(128).chr(158);
  }
  else if($ord == 133) {
    return chr(226).chr(128).chr(166);
  }
  else if($ord == 134) {
    return chr(226).chr(128).chr(160);
  }
  else if($ord == 135) {
    return chr(226).chr(128).chr(161);
  }
  else if($ord == 136) {
    return chr(203).chr(134);
  }
  else if($ord == 137) {
    return chr(226).chr(128).chr(176);
  }
  else if($ord == 138) {
    return chr(197).chr(160);
  }
  else if($ord == 139) {
    return chr(226).chr(128).chr(185);
  }
  else if($ord == 140) {
    return chr(197).chr(146);
  }
  else if($ord == 141) {
    return chr(239).chr(191).chr(189);
  }
  else if($ord == 142) {
    return chr(197).chr(189);
  }
  else if($ord == 143) {
    return chr(239).chr(191).chr(189);
  }
  else if($ord == 144) {
    return chr(239).chr(191).chr(189);
  }
  else if($ord == 145) {
    return chr(226).chr(128).chr(152);
  }
  else if($ord == 146) {
    return chr(226).chr(128).chr(153);
  }
  else if($ord == 147) {
    return chr(226).chr(128).chr(156);
  }
  else if($ord == 148) {
    return chr(226).chr(128).chr(157);
  }
  else if($ord == 149) {
    return chr(226).chr(128).chr(162);
  }
  else if($ord == 150) {
    return chr(226).chr(128).chr(147);
  }
  else if($ord == 151) {
    return chr(226).chr(128).chr(148);
  }
  else if($ord == 152) {
    return chr(203).chr(156);
  }
  else if($ord == 153) {
    return chr(226).chr(132).chr(162);
  }
  else if($ord == 154) {
    return chr(197).chr(161);
  }
  else if($ord == 155) {
    return chr(226).chr(128).chr(186);
  }
  else if($ord == 156) {
    return chr(197).chr(147);
  }
  else if($ord == 157) {
    return chr(239).chr(191).chr(189);
  }
  else if($ord == 158) {
    return chr(197).chr(190);
  }
  else if($ord == 159) {
    return chr(197).chr(184);
  }
  else if($ord == 160) {
    return chr(194).chr(160);
  }

  if ($ord < 128) {
    return chr($ord);
  }
  else if ($ord < 2048) {
    $no_bytes = 2;
  }
  else if ($ord < 65536) {
    $no_bytes = 3;
  }
  else if ($ord < 1114112) {
    $no_bytes = 4;
  }
  else {
    return;
  }

  switch ($no_bytes) {
    case 2:
      $prefix = array(31, 192);
      break;

    case 3:
      $prefix = array(15, 224);
      break;

    case 4:
      $prefix = array(7, 240);
      break;
  }

  for ($i = 0; $i < $no_bytes; $i++) {
    $byte[$no_bytes - $i - 1] = (($ord & (63 * pow(2, 6 * $i))) / pow(2, 6 * $i)) & 63 | 128;
  }

  $byte[0] = ($byte[0] & $prefix[0]) | $prefix[1];

  $ret = '';
  for ($i = 0; $i < $no_bytes; $i++) {
    $ret .= chr($byte[$i]);
  }

  return $ret;
}

/**
 * Private function; Convert named entities to UTF-8 characters
 * from: http://pl2.php.net/manual/en/function.html-entity-decode.php#51722
 */
function _parse_name_entities(&$data) {
  static $ttr;
  if (!$ttr) {
    $trans_tbl = get_html_translation_table(HTML_ENTITIES);
    foreach ($trans_tbl as $k => $v) {
      $ttr[$v] = utf8_encode($k);
    }
    $ttr['&apos;'] = "'";
  }
  return strtr($data, $ttr);
}

/**
 * Private function; Convert all entities to UTF-8 characters
 */
function parse_entities(&$data) {
  $result = _parse_name_entities($data);
  return preg_replace_callback('/&#([0-9a-fx]+);/mi', '_parse_num_entity', $result);
}


/**
 * Private function; Convert relative URLs
 */
function parse_relative_urls(&$data, $base_url) {
  $src = '%( href| src)="(?!\w+://)/?([^"]*)"%';
  $dst = '$1="'. trim($base_url, '/') .'/$2"';
  return preg_replace($src, $dst, $data);
}

class LeechNewsParser {
  var $xml_parser;

  var $xml_tree;
  var $xml_paths;
  var $xml_path_cur;
  var $xml_timer;

  var $_start;
  var $_end;

  function LeechNewsParser() {
    $this->xml_parser = NULL;
    $this->xml_tree = array();
    $this->xml_paths[] = &$this->xml_tree;
    $this->xml_path_cur = 0;
    $this->xml_timer = 0;
    $this->_start = 0;
    $this->_end = 0;
  }

  function Parse(&$data) {
    $this->xml_tree = array();
    $this->xml_paths[] = &$this->xml_tree;
    $this->xml_path_cur = 0;

    $this->_start = microtime();

    $this->xml_parser = drupal_xml_parser_create($data);
    if ($this->xml_parser == NULL) {
      return $this->xml_tree;
    }

    xml_set_object($this->xml_parser, $this);
    xml_set_element_handler($this->xml_parser, '_element_start', '_element_end');
    xml_set_character_data_handler($this->xml_parser, '_element_data');
    xml_parser_set_option($this->xml_parser, XML_OPTION_CASE_FOLDING, 1);
    xml_parser_set_option($this->xml_parser, XML_OPTION_SKIP_WHITE, 1);
    if (!xml_parse($this->xml_parser, $data, 1)) {
      $this->xml_tree['parser_error'] = xml_error_string(xml_get_error_code($this->xml_parser));
      $this->xml_tree['parser_line'] = xml_get_current_line_number($this->xml_parser);
    }
    else {
       unset($this->xml_tree['parser_error']);
       unset($this->xml_tree['parser_line']);
    }
    xml_parser_free($this->xml_parser);

    $this->_end = microtime();
    list($sec, $usec) = explode(' ', $this->_start);
    $this->_start = $sec + $usec;
    list($sec, $usec) = explode(' ', $this->_end);
    $this->xml_tree['parser_time'] = $this->xml_timer = ($sec + $usec) - $this->_start;

    return $this->xml_tree;
  }

  function _element_start($parser, $name, $attributes) {
    $temp = &$this->xml_paths[$this->xml_path_cur++];
    $temp[$name][] = $attributes;
    $this->xml_paths[$this->xml_path_cur] = &$temp[$name][count($temp[$name])-1];
  }

  function _element_end($parser, $name) {
    $temp = &$this->xml_paths[$this->xml_path_cur];
    array_pop($this->xml_paths);
    $this->xml_path_cur--;
    if (isset($temp['VALUE'])) {
      $temp['VALUE'] = trim(parse_entities($temp['VALUE']));
    }
  }

  function _element_data($parser, $data) {
    $temp = trim($data);
    if (strlen($temp) > 0) {
      $temp = &$this->xml_paths[$this->xml_path_cur];
      $temp['VALUE'] .= $data;
    }
  }
}

?>
