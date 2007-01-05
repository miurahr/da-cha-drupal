<?php
// $Id: field_external_attachment.inc,v 1.1 2006/10/17 07:21:50 ber Exp $

function flexinode_field_external_attachment_name($field) {
  return t('external attachment');
}

function flexinode_field_external_attachment_form($field, &$node) {
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

function flexinode_field_external_attachment_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_external_attachment_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_external_attachment_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_external_attachment_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return check_plain($node->$fieldname);
}

function flexinode_field_external_attachment_config($field) {
  return array('default_value' => array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $field->default_value,
    ));
}

function flexinode_field_external_attachment_rss($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  return array('key' => 'enclosure', 'attributes' => array('url' => $node->$fieldname));
}

function flexinode_field_external_attachment_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;

  if (!(empty($node->$fieldname) || valid_url($node->$fieldname, true) || valid_url($node->$fieldname))) {
    form_set_error($node->$fieldname, t('The URL %url is not valid.', array('%url' => theme('placeholder', $node->$fieldname))));
    return;
  }

  $response = drupal_http_request($node->$fieldname, array(), 'HEAD');
  if (isset($response->error)) {
    form_set_error($fieldname, t('The URL %url is invalid: %error.', array('%url' => theme('placeholder', $node->$fieldname), '%error' => t($response->error))));
  }
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
function theme_flexinode_external_attachment($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, l($formatted_value, $formatted_value));
  $output = '<div class="flexinode-external-attachment-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */
