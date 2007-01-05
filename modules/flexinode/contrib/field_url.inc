<?php
// $Id: field_url.inc,v 1.10 2005/11/10 09:32:14 crunchywelch Exp $

function flexinode_field_url_name($field) {
  return t('URL');
}

function flexinode_field_url_form($field, &$node, $error) {
  $fieldname = 'flexinode_'. $field->field_id;
  return array($fieldname => array(
    '#type' => 'textfield',
    '#title' => t($field->label),
    '#default_value' => isset($node->$fieldname) ? $node->$fieldname : $field->default_value,
    '#description' => t($field->description),
    '#required' => $field->required,
    '#weight' => $field->weight,
    ));
}

function flexinode_field_url_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_url_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_url_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_url_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;

  // If the URL is empty, or it validates as an absolute URL, or it validates
  // as a relative URL, the URL is considered valid.
  if (!(empty($node->$fieldname) || valid_url($node->$fieldname, true) || valid_url($node->$fieldname))) {
    form_set_error($node->$fieldname, t('The url is not valid.'));
  }
}

function flexinode_field_url_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $output = check_plain($node->$fieldname);
  return $output ? '<a href="'.(ERegI('^[a-z0-9_]+://', $output) ? $output:'http://'.$output) .'">'. $output .'</a>' : '';
}

function flexinode_field_url_config($field) {
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
function theme_flexinode_url($field_id, $label, $value, $formatted_value) {
  return theme('form_element', $label, $formatted_value);
}

/** @} End of addtogroup themeable */

