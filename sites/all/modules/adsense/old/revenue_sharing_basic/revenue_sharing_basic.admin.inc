<?php
// $Id: revenue_sharing_basic.admin.inc,v 1.3.2.3 2008/09/11 22:52:00 jcnventura Exp $

/**
 * @file
 * Contains the administrative functions of the revenue_sharing_basic
 * module.
 *
 * This file is included by the basic revenue sharing  module, and includes
 * the settings form.
 */

/**
 * Menu callback for the revenue_sharing_basic module settings form.
 *
 * @ingroup forms
 */
function revenue_sharing_basic_settings() {
  include_once(drupal_get_path('module', 'revenue_sharing_basic') .'/help/revenue_sharing_basic.help.inc');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => revenue_sharing_basic_help_text(),
  );

  $form['required'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#title'       => t('Required parameters'),
  );

  $form['required']['revenue_sharing_basic_client_id_profile_field'] = array(
    '#type'          => 'select',
    '#title'         => t('Google AdSense client ID profile field'),
    '#default_value' => variable_get('revenue_sharing_basic_client_id_profile_field', REVENUE_SHARING_BASIC_CLIENT_ID_PROFILE_FIELD_DEFAULT),
    '#options'       => revenue_sharing_basic_get_profile_fields(),
    '#required'      => TRUE,
    '#description'   => t('This is the profile field that holds the AdSense Client ID for the site owner as well as (optionally) for site users who participate in revenue sharing. You must enabled the profile module and create a new field for this.'),
  );

  $form['revenue'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#title'       => t('Revenue sharing options'),
  );

  $form['revenue']['revenue_sharing_basic_revenue_enable'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable revenue sharing'),
    '#return_value'  => 1,
    '#default_value' => variable_get('revenue_sharing_basic_revenue_enable', REVENUE_SHARING_BASIC_REVENUE_ENABLE_DEFAULT),
    '#description'   => t('Note that enabling this will disable AdSense code caching, which can cause more resource usage for busy sites. The referral feature requires the referral module to be installed.')
  );

  $form['revenue']['revenue_sharing_basic_percentage_author'] = array(
    '#type'          => 'select',
    '#title'         => t('Percentage of node views going to author'),
    '#default_value' => variable_get('revenue_sharing_basic_percentage_author', REVENUE_SHARING_BASIC_PERCENTAGE_AUTHOR_DEFAULT),
    '#options'       => drupal_map_assoc(array(0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 75, 80, 90, 100)),
  );

  if (module_exists('referral')) {
    $form['revenue']['revenue_sharing_basic_percentage_refer'] = array(
      '#type'          => 'select',
      '#title'         => t('Percentage of node views going to user who referred the author'),
      '#default_value' => variable_get('revenue_sharing_basic_percentage_refer', REVENUE_SHARING_BASIC_PERCENTAGE_REFER_DEFAULT),
      '#options'       => drupal_map_assoc(array(0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 75, 80, 90, 100)),
      '#description'   => t('This feature requires the referral module to be installed.')
    );
  }

  $form['#redirect'] = 'admin/settings/adsense/id';

  return system_settings_form($form);
}

/**
 * Auxiliary function to create the list for the revenue_sharing_basic_client_id_profile_field field
 *
 * @return
 *   array of fields with the field IDs as keys and the field titles as values
 *
 * @ingroup forms
 */
function revenue_sharing_basic_get_profile_fields() {
  $profile_list = array(0 => 'None');

  $result = db_query("SELECT fid, title FROM {profile_fields} ORDER BY fid");
  while ($row = db_fetch_object($result)) {
    $profile_list[$row->fid] = $row->title;
  }

  return $profile_list;
}
