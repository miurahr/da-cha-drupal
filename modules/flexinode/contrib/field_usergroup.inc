<?php
// $Id: field_usergroup.inc,v 1.3 2006/01/17 15:00:07 morbus Exp $

function flexinode_field_usergroup_name($field) {
  return t('user group');
}

function flexinode_field_usergroup_form($field, &$node) {
  $fieldname = 'flexinode_'. $field->field_id;

  if ($field->options) {
    $where_roles = array();
    foreach ($field->options as $option => $value) {
      if($value) {
        $where_roles[] = "rid = $option";
      }
    }
    $where_sql = implode(' OR ', $where_roles);
  }

  $result = db_query('SELECT DISTINCT(ur.uid), name FROM {users_roles} ur, {users} u WHERE (%s) AND ur.uid = u.uid ORDER BY name', $where_sql);
  $selectable_users = array(); // stores 'em all.
  $selectable_users[-1] = '<'. t('none') .'>';
  while ($user = db_fetch_object($result)) {
    $selectable_users[$user->uid] = $user->name;
  }

  return array($fieldname => array(
    '#type' => 'select',
    '#title' => t($field->label),
    '#options' => $selectable_users,
    '#default_value' => $node->$fieldname,
    '#description' => t($field->description),
    '#weight' => $field->weight,
    '#required' => $field->required,
    ));
}

function flexinode_field_usergroup_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.numeric_data AS '. $fieldname;
}

function flexinode_field_usergroup_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.numeric_data';
}

function flexinode_field_usergroup_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, numeric_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, $node->$fieldname);
}

function flexinode_field_usergroup_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $user = db_fetch_object(db_query('SELECT name FROM {users} WHERE uid = %d', $node->$fieldname));
  return check_plain($user->name);
}

function flexinode_field_usergroup_config($field) {
  if(is_array($field->options)) {
    foreach($field->options as $key => $value) {
      if($value) {
        $options[] = $key;
      }
    }
  }

  return array('options' => array(
    '#type' => 'checkboxes',
    '#options' => user_roles(TRUE),
    '#title' => t('Roles to display users from'),
    '#default_value' => $options,
    '#description' => t('Select at least one role. All users from selected roles will be shown in a dropdown menu.'),
    '#required' => TRUE,
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
function theme_flexinode_usergroup($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-usergroup-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */
