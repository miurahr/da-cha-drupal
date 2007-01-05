<?php
// $Id: field_textarea.inc,v 1.19 2006/04/29 18:26:08 ber Exp $

function flexinode_field_textarea_name($field) {
  return t('text area');
}

function flexinode_field_textarea_form($field, &$node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $formatname = 'flexinode_'. $field->field_id .'_format';
  $form[$fieldname.'_filter'] = array(
    '#weight' => $field->weight,
  );

  $form[$fieldname.'_filter'][$fieldname] = array(
    '#type' => 'textarea',
    '#title' => t($field->label), 
    '#default_value' => isset($node->$fieldname) ? $node->$fieldname : $field->default_value,
    '#rows' => $field->rows,
    '#description' => t($field->description),
    '#required' => $field->required,
    '#weight' => $field->weight,
  );
  $form[$fieldname.'_filter'][$formatname] = filter_form($node->$formatname, $field->weight + 1, array($formatname));
  return $form;
}

function flexinode_field_textarea_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  $formatname = 'flexinode_'. $field->field_id .'_format';
  return $fieldname .'.textual_data AS '. $fieldname .', '. $fieldname .'.numeric_data AS '. $formatname;
}

function flexinode_field_textarea_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $formatname = 'flexinode_'. $field->field_id .'_format';
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data, numeric_data) VALUES (%d, %d, '%s', %d)", $node->nid, $field->field_id, $node->$fieldname, $node->$formatname);
}

function flexinode_field_textarea_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $formatname = 'flexinode_'. $field->field_id .'_format';
  if (!filter_access($node->$formatname)) {
    form_set_error($fieldname, t('The supplied input format is invalid.'));
  }
}

function flexinode_field_textarea_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $formatname = 'flexinode_'. $field->field_id .'_format';
  if ($node->$fieldname) {
    if ($brief) {
      return check_markup(node_teaser($node->$fieldname, $node->$formatname), $node->$formatname, FALSE);
    }
    else {
      return check_markup($node->$fieldname, $node->$formatname, FALSE);
    }
  }
}

function flexinode_field_textarea_config($field) {
  $form['default_value'] = array(
    '#type' => 'textarea',
    '#title' => t('Default value'),
    '#default_value' => $field->default_value,
    );
  $form['rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Lines'),
    '#default_value' => $field->rows ? $field->rows : 5,
    '#maxlength' => 10,
    '#description' => t('How large the text area will be.')
    );
  return $form;
}


/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format a text area for display in a node.
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
function theme_flexinode_textarea($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-textarea-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */

