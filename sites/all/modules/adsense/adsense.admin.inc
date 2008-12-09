<?php
// $Id: adsense.admin.inc,v 1.1.2.3 2008/09/11 22:51:59 jcnventura Exp $

/**
 * @file
 * Contains the administrative functions of the adsense module.
 *
 * This file is included by the core adsense module, and includes the
 * settings form.
 */

/**
 * Menu callback for the adsense module settings form.
 *
 * @ingroup forms
 */
function adsense_main_settings() {
  include_once(drupal_get_path('module', 'adsense') .'/help/adsense.help.inc');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_help_text(),
  );

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Visibility'),
  );

  $form['visibility']['adsense_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show AdSense on specific pages'),
    '#default_value' => variable_get('adsense_visibility', ADSENSE_VISIBILITY_DEFAULT),
    '#options' => array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.')),
  );

  $form['visibility']['adsense_access_pages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('adsense_access_pages', ADSENSE_ACCESS_PAGES_DEFAULT),
    '#rows' => 3,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are  %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Advanced options'),
  );

  $form['advanced']['adsense_test_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable test mode?'),
    '#default_value' => variable_get('adsense_test_mode', ADSENSE_TEST_MODE_DEFAULT),
    '#description' => t('This enables you to test the AdSense module settings. This can be useful in some situations: for example, testing whether revenue sharing is working properly or not without having to display real ads on your site. It is best to test this after you log out.'),
  );

  $form['advanced']['adsense_disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Google AdSense ads?'),
    '#default_value' => variable_get('adsense_disable', ADSENSE_DISABLE_DEFAULT),
    '#description' => t('This disables all display of Google AdSense ads from your web site. This is useful in certain situations, such as site upgrades, or if you make a copy of the site for development and test purposes.'),
  );

  $form['advanced']['adsense_placeholder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Placeholder when ads are disabled?'),
    '#default_value' => variable_get('adsense_placeholder', ADSENSE_PLACEHOLDER_DEFAULT),
    '#description' => t('This causes an empty box to be displayed in place of the ads when they are disabled.'),
  );

  $form['advanced']['adsense_placeholder_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Placeholder text to display'),
    '#default_value' => variable_get('adsense_placeholder_text', ADSENSE_PLACEHOLDER_TEXT_DEFAULT),
    '#rows' => 3,
    '#description' => t('Enter any text to display as a placeholder when ads are disabled.'),
  );

  $form['advanced']['adsense_section_targeting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable AdSense section targeting?'),
    '#default_value' => variable_get('adsense_section_targeting', ADSENSE_SECTION_TARGETING_DEFAULT),
    '#description' => t('This better targets Google ads to the teaser and body of nodes.'),
  );

  return system_settings_form($form);
}

/**
 * Menu callback for the adsense publisher ID settings form.
 *
 * @ingroup forms
 */
function adsense_id_settings() {
  include_once(drupal_get_path('module', 'adsense') .'/help/adsense_id_help.inc');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_id_help_text(),
  );

  $form['adsense_basic_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Site Google AdSense Publisher ID'),
    '#required'      => TRUE,
    '#default_value' => variable_get('adsense_basic_id', ADSENSE_BASIC_ID_DEFAULT),
    '#description'   => t('This is the Google AdSense Publisher ID for the site owner. It is used if no other ID is suitable. Get this in your Google Adsense account. It should be similar to %id.', array('%id' => 'pub-9999999999999')),
  );

  $options = _adsense_id_settings_client_id_mods();
  if (count($options) > 1) {
    $form['adsense_id_module'] = array(
      '#type'          => 'radios',
      '#title'         => t('Publisher ID module'),
      '#default_value' => variable_get('adsense_id_module', ADSENSE_ID_MODULE_DEFAULT),
      '#options'       => $options,
    );
  }
  else {
    $form['adsense_id_module'] = array(
      '#type'  => 'hidden',
      '#value' => $options[0],
    );
  }

  $form['#validate'][] = '_adsense_id_settings_validate';

  return system_settings_form($form);
}

/**
 * Validate adsense_id_settings form.
 */
function _adsense_id_settings_validate($form, &$form_state) {
  $form_state['values']['adsense_basic_id'] = trim($form_state['values']['adsense_basic_id']);
}

/**
 * Search for the available Publisher ID modules
 *
 * @return
 *   array of selectable Publisher ID functions
 */
function _adsense_id_settings_client_id_mods() {
  $ret['adsense_basic'] = 'Use the site Publisher ID always';

  $funcs = get_defined_functions();
  foreach ($funcs['user'] as $func) {
    if (preg_match('!_adsense$!', $func)) {
      $settings = $func('settings');
      $ret[$func] = $settings['name'];
      if (!empty($settings['desc'])) {
        $ret[$func] .= "<div style='margin-left: 2.5em;' class='description'>{$settings['desc']}</div>";
      }
    }
  }
  return $ret;
}
