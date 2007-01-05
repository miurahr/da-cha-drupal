<?php
// $Id: field_address.inc,v 1.1 2005/12/26 20:51:31 njivy Exp $

function flexinode_field_address_name($field) {
  return t('postal address');
}

function flexinode_field_address_form($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $values = $node->$fieldname;

  $form['address']['#type'] = 'fieldset';
  $form['address']['#title'] = $field->label;
  $form['address']['#weight'] = $field->weight;
  $form['address']['#collapsible'] = TRUE;
  $form['address']['#collapsed'] = FALSE;
  $form['address'][$fieldname .'_address_1'] = array(
    '#type' => 'textfield',
    '#default_value' => $values['address_1']
    );
  $form['address'][$fieldname .'_address_2'] = array(
    '#type' => 'textfield',
    '#default_value' => $values['address_2']
    );
  $form['address'][$fieldname .'_address_3'] = array(
    '#type' => 'textfield',
    '#default_value' => $values['address_3']
    );
  $form['address'][$fieldname .'_city'] = array(
    '#type' => 'textfield',
    '#prefix' => '<div class="container-inline">',
    '#size' => 20,
    '#default_value' => $values['city'],
    '#description' => t('city')
    );
  $form['address'][$fieldname .'_state'] = array(
    '#type' => 'textfield',
    '#size' => 2,
    '#default_value' => $values['state'],
    '#description' => t('state')
    );
  $form['address'][$fieldname .'_postal_code'] = array(
    '#type' => 'textfield',
    '#suffix' => '</div>',
    '#size' => 10,
    '#default_value' => $values['postal_code'],
    '#description' => t('postal code')
    );
  $form['address'][$fieldname .'_country'] = array(
    '#type' => 'textfield',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#size' => 20,
    '#default_value' => $values['country'],
    '#description' => t('country')
    );
  return $form;
}

function flexinode_field_address_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.serialized_data AS '. $fieldname;
}

function flexinode_field_address_load($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $address = unserialize($node->$fieldname);
  return $address;
}

function flexinode_field_address_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_address_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $address['address_1'] = $node->{$fieldname . '_address_1'};
  $address['address_2'] = $node->{$fieldname . '_address_2'};
  $address['address_3'] = $node->{$fieldname . '_address_3'};
  $address['city'] = $node->{$fieldname . '_city'};
  $address['state'] = $node->{$fieldname . '_state'};
  $address['postal_code'] = $node->{$fieldname . '_postal_code'};
  $address['country'] = $node->{$fieldname . '_country'};

  $key = md5(implode(', ', $address));
  $serialized = serialize($address);

  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data, serialized_data) VALUES (%d, %d, '%s', '%s')", $node->nid, $field->field_id, $key, $serialized);
}

function flexinode_field_address_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $node->$fieldname;
}

/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format an address for display in a node.
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
function theme_flexinode_address($field_id, $label, $value, $formatted_value) {
  $output = '<div class="address_1">' . $formatted_value['address_1'] . "</div>\n";
  $output .= '<div class="address_2">' . $formatted_value['address_2'] . "</div>\n";
  $output .= '<div class="address_3">' . $formatted_value['address_3'] . "</div>\n";

  $output .= '<div class="container-inline">';
  $output .= '<div class="city">' . $formatted_value['city'] . '</div>';
  $output .= '<div class="state">' . $formatted_value['state'] . '</div>';
  $output .= '<div class="postal_code">' . $formatted_value['postal_code'] . '</div>';
  $output .= "</div>\n";

  $output .= '<div class="country">' . $formatted_value['country'] . "</div>\n";

  $output = theme('form_element', $label, $output);
  $output = '<div class="flexinode-address-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */
?>
