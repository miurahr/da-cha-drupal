<?php

if(!function_exists('form_colorpicker')){
  include_once "colorpickerform.inc";
}

function flexinode_field_colorpicker_name($field) {
  return t('color picker');
}

function flexinode_field_colorpicker_form($field, &$node) {
  $fieldname = 'flexinode_'. $field->field_id;
  return form_colorpicker(t($field->label), $fieldname, isset($node->$fieldname) ? $node->$fieldname : $field->default_value,  $field->required);
}

function flexinode_field_colorpicker_validate($field, $node) { 
	$fieldname = 'flexinode_'. $field->field_id;
	if(!preg_match('/^#[0-9A-F]{3,3}$/i', $node->$fieldname) &&
		!preg_match('/^#[0-9A-F]{6,6}$/i', $node->$fieldname)){
		return array('value' => $node->$fieldname, 
					 'error' => t('Must be a valid color format: e.g. #CCC or #1144AA.'));			
	}
	return array('value' => $node->$fieldname);
}		

function flexinode_field_colorpicker_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_colorpicker_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_colorpicker_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_colorpicker_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return check_plain($node->$fieldname).'<div style="background-color: '.$node->$fieldname.'; padding: 1; height: 21px; width: 50px"><div style="height: 100%; width: 100%"></div></div>';
}

function flexinode_field_colorpicker_config($field, $edit) {
  $output = form_colorpicker(t('Default value'), 'default_value', isset($field->default_value) ? $field->default_value : NULL, $edit['default_value']);
  return $output;		
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
function theme_flexinode_colorpicker($field_id, $label, $value, $formatted_value) {
	return $formatted_value;
}

/** @} End of addtogroup themeable */

?>
