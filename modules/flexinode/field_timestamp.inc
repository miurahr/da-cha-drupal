<?php
// $Id: field_timestamp.inc,v 1.12 2006/04/29 19:22:56 ber Exp $

function flexinode_field_timestamp_name($field) {
  return t('date/time');
}

function flexinode_field_timestamp_form($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  return flexinode_form_date($node->$fieldname, $field);
}

function flexinode_field_timestamp_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.numeric_data AS '. $fieldname;
}

function flexinode_field_timestamp_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.numeric_data';
}

function flexinode_field_timestamp_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $stamp = flexinode_validate_date($node, $fieldname);
  db_query('INSERT INTO {flexinode_data} (nid, field_id, numeric_data) VALUES (%d, %d, %d)', $node->nid, $field->field_id, $stamp);
}

function flexinode_field_timestamp_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return format_date($node->$fieldname);
}


/**
 * A copy of event_form_date().
 */
function flexinode_form_date($timestamp, $field) {
  $prefix = 'flexinode_'. $field->field_id;

  //determine settings for form's hour selector
  if (variable_get('event_ampm', '0')) {
    $hour_format = t('g');
    $first_hour = 1;
    $last_hour = 12;
  }
  else {
    $hour_format = t('H');
    $first_hour = 0;
    $last_hour = 23;
  }

  if(!$timestamp) {
    $timestamp = time();
    // Round to nearest hour:
    $timestamp -= $timestamp % (60 * 60);
  }

  $months = array(1 => t('January'), t('February'), t('March'), t('April'), t('May'), t('June'), t('July'), t('August'), t('September'), t('October'), t('November'), t('December'));
  for ($i = 1; $i <= 31; $i++) $days[$i] = $i;
  for ($i = $first_hour; $i <= $last_hour; $i++) $hours[$i] = $i;
  for ($i = 0; $i <= 59; $i++) $minutes[$i] = $i < 10 ? "0$i" : $i;
  $am_pms = array('am' => t('am'), 'pm' => t('pm'));

  // Use format_date(), it handles user timezone and locale.
  $year = format_date($timestamp, 'custom', 'Y');
  $month = format_date($timestamp, 'custom', 'm');
  $day = format_date($timestamp, 'custom', 'd');
  $hour = format_date($timestamp, 'custom', $hour_format);
  $minute = format_date($timestamp, 'custom', 'i');
  $am_pm = format_date($timestamp, 'custom', 'a');

  $form[$prefix]['#type'] = 'fieldset';
  $form[$prefix]['#title'] = $field->label;
  $form[$prefix]['#weight'] = $field->weight;
  $form[$prefix]['#prefix'] = '<div class="container-inline">';
  $form[$prefix]['#suffix'] = '</div>';
  $form[$prefix][$prefix .'_day'] = array(
    '#type' => 'textfield',
    '#default_value' => $day,
    '#maxlength' => 2,
    '#size' => 2,
    '#description' => t('day'),
    '#required' => TRUE,
    );
  $form[$prefix][$prefix .'_month'] = array(
    '#type' => 'select',
    '#default_value' => $month,
    '#options' => $months,
    '#description' => t('month'),
    '#required' => TRUE,
    );
  $form[$prefix][$prefix .'_year'] = array(
    '#type' => 'textfield',
    '#default_value' => $year,
    '#maxlength' => 4,
    '#size' => 4,
    '#description' => t('year'),
    '#required' => TRUE,
    );
  $form[$prefix][$prefix .'_hour'] = array(
    '#prefix' => '',
    '#type' => 'select',
    '#default_value' => $hour,
    '#options' => $hours,
    '#required' => TRUE,
    '#description' => t('hour'),
    );
  $form[$prefix][$prefix .'_minute'] = array(
    '#prefix' => ':',
    '#type' => 'select',
    '#default_value' => $minute,
    '#options' => $minutes,
    '#required' => TRUE,
    '#description' => t('minutes'),
    );
  if (variable_get('event_ampm', '0')) {
    $form[$prefix][$prefix .'_ampm'] = array(
      '#type' => 'radios',
      '#default_value' => $am_pm,
      '#options' => $am_pms,
      '#required' => TRUE,
      );
  }

  return $form;
}


function flexinode_validate_date(&$node, $prefix = '') {
  if (isset($node->{$prefix . '_year'}) && isset($node->{$prefix . '_month'}) && isset($node->{$prefix . '_day'}) && isset($node->{$prefix . '_hour'}) && isset($node->{$prefix . '_minute'})) {
    $hour = $node->{$prefix . '_hour'};
    if (variable_get('event_ampm', '0')) {
      if ($node->{$prefix . '_ampm'} == 'pm') {
        $hour += 12;
      }
      elseif ($hour == 12) {
        $hour -= 12;
      }
    }
    $result = gmmktime($hour, $node->{$prefix . '_minute'}, 0, $node->{$prefix . '_month'}, $node->{$prefix . '_day'}, $node->{$prefix . '_year'}) - $GLOBALS['user']->timezone;
  }
  else if (isset($node->$prefix)) {
    $result = $node->$prefix;
  }

  return $result;
}


/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format a timestamp for display in a node.
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
function theme_flexinode_timestamp($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-timestamp-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */
