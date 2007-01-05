<?php
// $Id: field_table.inc,v 1.5 2005/11/10 09:32:14 crunchywelch Exp $
function flexinode_field_table_name($field) {
  return t('table');
}

function flexinode_field_table_form($field, $node) {

  $fieldname = 'flexinode_'. $field->field_id;
  if ($node->$fieldname) {
    $table=$node->$fieldname;
    $rows=count($table)+1;
    $cols=count($table[0])+1;
  }
  else {
    $table=array();
    $rows=8;
    $cols=5;
  }

  $form['table'][$fieldname.'_rows'] = array(
    '#type' => 'hidden',
    '#value' => $rows,
    );

  $form['table']['#title'] = $field->label;
  $form['table']['#prefix'] = '<table>';
  $form['table']['#suffix'] = '</table>';
  for ($i = 0; $i < $rows; $i++) {
    $form['table'][$i]['#prefix'] = '<tr>';
    $form['table'][$i]['#suffix'] = '<tr>';
    for ($j = 0; $j < $cols; $j++) {
      $value = (isset($table[$i]) && isset($table[$i][$j])) ? $table[$i][$j] : '';
      $form['table'][$i][$fieldname.'_'.$j.']['] = array(
        '#type' => 'textarea',
        '#default_value' => $value,
        '#cols' => 10,
        '#rows' => 3,
        '#prefix' => '<td>',
        '#suffix' => '</td>',
        );
    }
  }

  return $form;
}

function flexinode_field_table_execute($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  if (!isset($_POST['edit'])) {
    return array('value' => $node->$fieldname);
  }
  $rows = $_POST['edit'][$fieldname.'_rows'];
  $value = array();
  $deleted_cols = array();
  foreach ($_POST['edit'][$fieldname.'_0'] as $key=>$val) {
    if (empty($val) && $key) {
      $deleted_cols[] = $key;
    }    
  }
  for ($i = 0; $i <= $rows; $i++) {
    if ($i && empty($_POST['edit'][$fieldname.'_'.$i][0])) {
      continue;
    }
    $newrow = $_POST['edit'][$fieldname.'_'.$i];
    foreach ($deleted_cols as $key)
      unset($newrow[$key]);
    $value[] = array_values($newrow); // reindex from 0
  }
  return $value;
}

function flexinode_field_table_insert($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  db_query("INSERT INTO {flexinode_data} (nid, field_id, serialized_data) VALUES (%d, %d, '%s')", $node->nid, $field->field_id, serialize($node->$fieldname));
}

function flexinode_field_table_db_select($field) {
  $fieldname = 'flexinode_'. $field->field_id;
  return $fieldname .'.serialized_data AS '. $fieldname;
}

function flexinode_field_table_load($field, $node) {
  $fieldname = 'flexinode_'. $field->field_id;
  if (isset($table_phase)) $table_phase++; else $table_phase=0;
  return unserialize($node->$fieldname);
}


function flexinode_field_table_format($field, $node, $brief = 0) {
  $fieldname = 'flexinode_'. $field->field_id;
  $table = $node->$fieldname;
  $output = "<table id=$fieldname>";
  $i=0;
  foreach ($table as $row) {
    $output .= '<tr class="'.$fieldname.'_'.$i.'"><td>'.implode('</td><td>',$row).'</td></tr>';
    $i=1-$i;
  }
  $output .= "</table>";
  return $output;
}

function theme_flexinode_table($field_id, $label, $value, $formatted_value) {
  $output = theme('form_element', $label, $formatted_value);
  $output = '<div class="flexinode-table-'. $field_id .'">'. $output .'</div>';
  return $output;
}

