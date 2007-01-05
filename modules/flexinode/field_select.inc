<?php
// $Id: field_select.inc,v 1.12 2006/04/14 12:32:36 ber Exp $

function flexinode_field_select_name($field) {
  return t('dropdown menu');
}

function flexinode_field_select_form($field, &$node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $options = array(0 => '<'. t('none') .'>');
  foreach ($field->options as $option) {
    $options[] = $option;
  }
  if ($field->required) {
    unset($options[0]);
  }
  return array($fieldname => array(
    '#type' => 'select',
    '#title' => t($field->label),
    '#default_value' => $node->$fieldname,
    '#options' => $options,
    '#description' => t($field->description),
    '#required' => $field->required,
    '#weight' => $field->weight,
  ));
}

function flexinode_field_select_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.numeric_data AS '. $fieldname;
}

function flexinode_field_select_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.numeric_data';
}

function flexinode_field_select_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query('INSERT INTO {flexinode_data} (nid, field_id, numeric_data) VALUES (%d, %d, %d)', $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_select_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $node->$fieldname ? $field->options[$node->$fieldname] : FALSE;
}

function flexinode_field_select_config($field, $edit) {
  $field_options = (array) $field->options;
  return array('options' => array(
    '#type' => 'textarea',
    '#default_value' => is_array($edit['options']) ? implode('|', $edit['options']) : implode('|', $field_options),
    '#description' => t('Please enter a pipe delimited list of options with no carriage returns. For example: "Red|Blue|Green" or "Small|Medium|Large"'),
    ));
}


/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format a dropdown selection for display in a node.
 *
 * @param field_id
 *   Which field is being displayed (useful when overriding this function
 *   if you want to style one particular field differently).
 * @param label
 *   The label for the field as displayed on the node form.
 * @param value
 *   The value that the user entered for the field.
 * @param formatted_value
 *   The displayed label for the selected value
 */
function theme_flexinode_select($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-select-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */

