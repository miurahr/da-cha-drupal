<?php
// $Id: field_email.inc,v 1.10 2005/11/10 09:32:14 crunchywelch Exp $

function flexinode_field_email_name($field) {
  return t('e-mail address');
}

function flexinode_field_email_form($field, &$node, $error) {
  $fieldname = 'flexinode_'. $field->field_id;

  if (isset($node->$fieldname) && strpos($node->$fieldname, '&#') === 0) {
    $value = flexinode_unhtmlentities($node->$fieldname);
  }
  else {
    $value = $node->$fieldname;
  }
  return array($fieldname => array(
    '#type' => 'textfield',
    '#title' => t($field->label),
    '#default_value' => $value ? $value : $field->default_value,
    '#description' => t($field->description),
    '#weight' => $field->weight,
    ));
}

function flexinode_field_email_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_email_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_email_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $node->$fieldname = htmlentities($node->$fieldname);
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_email_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  if(!(empty($node->$fieldname) || valid_email_address($node->$fieldname))) {
   form_set_error($fieldname, t('The email address is not valid.'));
  }
}

function flexinode_field_email_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $output = check_plain($node->$fieldname);
  return $output ? '<a href="&#109;&#97;&#105;&#108;&#116;&#111;&#58;'. $output .'">'. $output .'</a>' : '';
}

function flexinode_field_email_config($field, $edit) {
  return array('default_value' => array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $field->default_value,
    ));
}


/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format a single-line text field for display in a node.
 *
 * @param field_id
 *   Which field is being displayed (useful when overriding this function
 *   if you want to style one particular field differently).
 * @param label
 *   The label for the field as displayed on the node form.
 * @param value
 *   The value that the user entered for the field.
 * @param formatted_value
 *   The value that the user entered for the field as pre-formatted by the module.
 */
function theme_flexinode_email($field_id, $label, $value, $formatted_value) {
  return theme('form_element', $label, $formatted_value);
}

/** @} End of addtogroup themeable */

function flexinode_unhtmlentities($string) {
   $trans_tbl = get_html_translation_table(HTML_ENTITIES);
   $trans_tbl = array_flip($trans_tbl);
   return strtr($string, $trans_tbl);
}

