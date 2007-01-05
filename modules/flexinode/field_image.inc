<?php
// $Id: field_image.inc,v 1.20 2006/04/26 11:43:34 ber Exp $

// FIXME: admin/settings/flexinode is empty. I don't know how to make it dissapear.
// We could add here default subforlder where to keep images (e.g. 'images'). Then each image field in 
// different flexinode types could have it's own image placeholder, you could set it e.g. to images/type1, images/type2 etc.

// FIXME: when editing (updating, changing) flexinode node flexinode_field_image_insert() is called and thumbnails/previews are generated
// even if no new file was uploaded... don't know how to fix that...

function flexinode_field_image_name($field) {
  return t('image');
}

function flexinode_field_image_form($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;

  if ($node->$fieldname) {
    $form[$fieldname .'_old'] = array(
      '#type' => 'hidden',
      '#value' => serialize($node->$fieldname),
      );
  }
  $form[$fieldname] = array(
    '#type' => 'file',
    '#title' => t($field->label),
    '#description' =>  ($node->$fieldname ? t('"%filename" has been uploaded. If you upload another file, the current file will be replaced.', array('%filename' => $node->$fieldname->filename)) : '') .' '. t($field->description) .' '. t('The file is limited to %kbKB and a resolution of %wxh pixels (width x height).', array('%wxh' => $field->options[1], '%kb' => $field->options[4])),
    '#required' => $field->required,
    '#weight' => $field->weight,
    );
  
  return $form;
}

function flexinode_field_image_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.serialized_data AS '. $fieldname;
}

function flexinode_field_image_db_sort_column($field) {
  return 'flexinode_'. $field->field_id .'.textual_data';
}

function flexinode_field_image_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  $node->$fieldname = file_save_upload($node->$fieldname, $node->$fieldname->filename);
  $node->$fieldname->smallpath = flexinode_field_image_make_smaller($node->$fieldname->filepath, '_sm', $field->options[2]);
  $node->$fieldname->thumbpath = flexinode_field_image_make_smaller($node->$fieldname->filepath, '_th', $field->options[3]);
  $serialized = is_object($node->$fieldname) ? serialize($node->$fieldname) : '';
  db_query("INSERT INTO {flexinode_data} (nid, field_id, textual_data, serialized_data) VALUES (%d, %d, '%s', '%s')", $node->nid, $field->field_id, $node->$fieldname->filename, $serialized);
  return $node;
}

function flexinode_field_image_make_smaller($path, $add, $size) {
    list($width, $height) = explode('x', $size);
    $dest_path = preg_replace('!(\.[^/.]+?)?$!', "$add\\1", $path, 1); // Add $add before extension. Works if there's no extension and with other stupid cases ;)
    
    if ($size = getimagesize($path)) {
      if ($size[0] > $width or $size[1] > $height) {
        image_scale($path, $dest_path, $width, $height);
        return $dest_path;
      }
      return $path;
    }
    return NULL;
}

function flexinode_field_image_delete($field, $node, $unconditional = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $result = db_fetch_object(db_query('SELECT serialized_data FROM {flexinode_data} WHERE nid = %d AND field_id = %d', $node->nid, $field->field_id));
  $file = unserialize($result->serialized_data);
  if ($unconditional || $node->$fieldname != $file) {
    file_delete($file->filepath);
    file_delete($file->thumbpath);
    file_delete($file->smallpath);
  }
}

function flexinode_field_image_validate($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  if($file = file_check_upload($fieldname)) {
    // check that uploaded file is an image, with a maximum file size and maximum height/width
    if ($size = @getimagesize($file->filepath)) {
      list($maxwidth, $maxheight) = explode('x', $field->options[1]);
      if ((!in_array($size[2], array(1, 2, 3)))) {
        form_set_error($fieldname, t('The uploaded file was not a valid image.'));
      }
      else if (@filesize($file->filepath) > ($field->options[4] * 1000)) {
        form_set_error($fieldname, t('The uploaded image is too large; the maximum file size is %num kB.', array('%num' => $field->options[4])));
      }
      else if ($size[0] > $maxwidth || $size[1] > $maxheight) {
        form_set_error($fieldname, t('The uploaded image is too large; the maximum dimensions are %nxn pixels.', array('%nxn' => $field->options[1])));
      }
    }
    else {
      form_set_error($fieldname, t('The uploaded file was not a valid image.'));
    }
  }
  elseif(!empty($node->$fieldname)) {
    form_set_error($fieldname, t('The image upload was not successful.'));
  }
}

function flexinode_field_image_execute($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  if ($file = file_save_upload($fieldname, variable_get('file_directory_path', NULL))) {
    return $file;
  }
  elseif(empty($node->$fieldname)) {
    return unserialize($node->{$fieldname .'_old'});
  }
}

function flexinode_field_image_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $file = is_object($node->$fieldname) ? $node->$fieldname : unserialize($node->$fieldname);
  if ($file) {
    if ($brief) {
      return '<a href="' . url('node/'. $node->nid) . '"><img alt="'. check_plain($node->title) .'" src="'. file_create_url($file->thumbpath) .'" /></a>';
    }
    else {
      $output = '<img alt="'. check_plain($node->title) .'" src="'. file_create_url($file->smallpath) .'" />';
      $output .= '<br /><a href="'. file_create_url($file->filepath) .'">'. t("Get original file (%fsKB)", array('%fs' => round(@filesize($file->filepath)/1024))) .'</a>';
      return $output;
    }
  }
}

function flexinode_field_image_load($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  return unserialize($node->$fieldname);
}

function flexinode_field_image_config($field) {

  if (!isset($field->options)) {
    $field->options = array(
      1 => '800x600',
      2 => '512x384',
      3 => '100x100',
      4 => 100,
    );
  }

  $form['tester'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#description' => t('Options for the image upload.'),
  );
  $form['tester'][] = array('options][1' => array(
    '#type' => 'textfield',
    '#title' => t('Maximum picture dimensions'),
    '#default_value' => $field->options[1],
    '#description' => t('Maximum dimensions for pictures. Format: WidthxHeight'),
    ));
  $form['tester'][] = array('options][2' => array(
    '#type' => 'textfield',
    '#title' => t('Preview dimensions'),
    '#default_value' => $field->options[2],
    '#description' => t('Dimensions for auto-created preview (scale will be preserved). Format: WidthxHeight'),
    ));
  $form['tester'][] = array('options][3' => array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail dimensions'),
    '#default_value' => $field->options[3],
    '#description' => t('Dimensions for auto-created thumbnail (scale will be preserved). Format: WidthxHeight'),
    ));
  $form['tester'][] = array('options][4' => array(
    '#type' => 'textfield',
    '#title' => t('Maximum picture size'),
    '#default_value' => $field->options[4],
    '#description' => t('Maximum picture file size, in kB.'),
    ));

  return $form;
}


/**
 * @addtogroup themeable
 * @{
 */

/**
 * Format an image for display in a node.
 *
 * @param field_id
 *   Which field is being displayed (useful when overriding this function
 *   if you want to style one particular field differently).
 * @param label
 *   The label for the field as displayed on the node form.
 * @param file
 *   The file that the user has uploaded. This is an object as provided
 *   by file.inc.
 * @param formatted_value
 *   The image as an HTML tag.
 */
function theme_flexinode_image($field_id, $label, $file, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-image-'. $field_id .'">'. $output .'</div>';
  return $output;
}

/** @} End of addtogroup themeable */

