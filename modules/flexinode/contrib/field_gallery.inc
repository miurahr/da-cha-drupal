<?php

function flexinode_field_gallery_name($field) {
  return t('image gallery');
}

function flexinode_field_gallery_form($field, &$node, $error) {
  $fieldname = 'flexinode_'. $field->field_id;

  if($vid = variable_get("image_nav_vocabulary", NULL)) {
    $terms = taxonomy_get_children($tid, $vid);
    foreach($terms as $name => $key) {
      $gals["t.".$key->tid] = $key->name;
    }
    $galleries = array_merge($gals);

    if(!is_array($node->$fieldname)) {
      $node->$fieldname = unserialize($node->$fieldname);
    }
    return form_select(t('Image Galleries'), $fieldname, $node->$fieldname, $galleries, t('The image galleries to associate.') . ' ' . theme('error', $error[$fieldname]), 0, 1);
  }
  else {
    form_set_error($fieldname, t('Warning: you must assign a vocabulary to navigate in image gallery. Fix in %url', array('%url'=>l(t('Site Configuration'), 'admin/settings/image#image_nav_vocabulary'))));
  }
}

function flexinode_field_gallery_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.textual_data AS '. $fieldname;
}

function flexinode_field_gallery_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_gallery_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, serialize($node->$fieldname));
}

function flexinode_field_gallery_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
}

function flexinode_field_gallery_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;

  $terms = taxonomy_get_children($tid, variable_get("image_nav_vocabulary", ""));
  foreach($terms as $name => $key) {
    $gals["t.".$key->tid] = $key->name;
  }
  $galleries = array_merge($gals);

  if(!is_array($node->$fieldname)) {
    $node->$fieldname = unserialize($node->$fieldname);
  }

  $output = '';  
  if ($node->$fieldname) {
    foreach($node->$fieldname as $key => $value) {
      $name = $galleries[$value];
      $output .= "<div class=\"event_gallery\">".l($name, "image/tid/".substr($value, 2), array('title'=>'Photo Gallery'))."</div>";
    }
  }

  return $output;
}

function flexinode_field_gallery_config($field, $edit) {
  //return form_textfield(t('Default value'), 'default_value', $edit['default_value'], 60, 128);
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
function theme_flexinode_gallery($field_id, $label, $value, $formatted_value) {
  return theme('form_element', $label, $formatted_value);
}

/** @} End of addtogroup themeable */

?>
