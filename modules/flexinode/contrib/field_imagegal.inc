<?php
/* 
 * $Id: field_imagegal.inc,v 1.3 2005/03/26 23:02:13 ustas Exp $
 */
 
function flexinode_field_imagegal_name($field) {
  return t('image gallery');
}

function flexinode_field_imagegal_form($field, &$node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $value = $node->$fieldname;
  $vacabularies = taxonomy_get_vocabularies('image');
  
  if ($vacabularies) {
    foreach ($vacabularies as $vocabulary) {
      // TODO: Better multiple image vacabularies support
      $output .= _taxonomy_term_select(t($field->label), $fieldname, $value, $vocabulary->vid, $vocabulary->description, $vocabulary->multiple, '<none>');
    }
  }
  return $output;
}

function flexinode_field_imagegal_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.numeric_data AS '. $fieldname;
}


function flexinode_field_imagegal_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.numeric_data';
}


function flexinode_field_imagegal_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $value = $node->$fieldname;
  $value = $value[0];
  db_query('INSERT INTO {flexinode_data} (nid, field_id, numeric_data) VALUES (%d, %d, %d)', $node->nid, $field->field_id, $value);
}


function flexinode_field_imagegal_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $tid = $node->$fieldname;
  
  if (!$brief) {
    // TODO: Refactoring of image module functionality. This should be made
    //       in a function in the image module:
    $thumb_num = variable_get("image_gallery_thumb_rows", "5") * variable_get("image_gallery_thumb_cols", "3");

    $sql = "SELECT n.nid, n.title, n.teaser, n.body, i.thumb_path FROM {node} n, {term_node} t, {image} i WHERE n.nid = t.nid AND n.nid = i.nid AND t.tid = '". $tid ."' AND i.personal = 0 AND n.moderate = 0 AND n.status = 1 ORDER BY ". _image_get_thumb_order();

    $result = pager_query($sql, $thumb_num, 0);
    while ($image = db_fetch_object($result)) {
      $images[] = $image;
    }
    $output = theme("image_gallery_album", $images);
  }
  else {
    $output = ($tid ? t('Yes') : t('No'));
  }
  return $output;
}

// TODO: May be it would be better to link to the gallery pages in tabular view
function flexinode_field_imagegal_search_form($field) {
  return null;
}

function flexinode_field_imagegal_search_clause($field, $edit) {
  return null;
}
// ----

function flexinode_field_imagegal_config($field, $edit) {
  return;
}

function theme_flexinode_imagegal($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  return $output;
}

?>
