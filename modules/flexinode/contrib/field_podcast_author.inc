<?php

function flexinode_field_podcast_author_name($field) {
  return t('podcast author');
}

function flexinode_field_podcast_author_form($field, &$node) {
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

function flexinode_field_podcast_author_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_podcast_author_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_podcast_author_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_podcast_author_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return check_plain($node->$fieldname);
}

function flexinode_field_podcast_author_config($field) {
  return array('default_value' => array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $field->default_value,
    ));
}

function flexinode_field_podcast_author_rss($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  return array('key' => 'author', 'value' => $node->$fieldname);
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
function theme_flexinode_podcast_author($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-podcast-author-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */
