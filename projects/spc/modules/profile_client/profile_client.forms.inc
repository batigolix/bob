<?php

/**
 * @file
 * TODO Auto generated file, add description.
 */

/**
 * Constructs settings form
 *
 * @param array $form
 *   Drupal form array.
 * @param array $form_state
 *   Drupal form_state array.
 *
 * @return array
 *   Drupal form array.
 */
function single_profile_tools_settings($form, &$form_state) {
  $form = array();
  
  $form['ws'] = array(
    '#type' => 'fieldset',
    '#title' => 'Web service',
  );

  $form['ws']['domain'] = array(
    '#title' => t('Web service domain'),
    '#type' => 'textfield',
    '#default_value' => variable_get('domain', ''),
    '#description' => t('E.g. "http://example.com". Do not include trailing slash'),
    );
  $form['ws']['endpoint'] = array(
    '#title' => t('Endpoint'),
    '#type' => 'textfield',
    '#default_value' => variable_get('endpoint', ''),
    '#description' => t('E.g. "web_service". Do not include trailing slash'),
    );
  
  $form['ws']['user'] = array(
    '#title' => t('User'),
    '#type' => 'textfield',
    '#default_value' => variable_get('user', ''),
  );
  
  $form['ws']['password'] = array(
    '#title' => t('Password'),
    '#type' => 'password',
    '#default_value' => variable_get('password', ''),
  );
  
  return system_settings_form($form);
}

/*

function tic_tools_import_dictionary_form($form, &$form_state) {
  $form = array();
  $letters = array();
  foreach (range('a', 'z') as $char) {
    $letters[$char] = strtoupper($char);
  }

  $form['letters'] = array(
      '#type' => 'checkboxes',
      '#options' => $letters,
      '#title' => 'Letters',
      '#default_value' => variable_get('letters', $letters),
  );
  
  $form['#attached']['css'] = array(
      drupal_get_path('module', 'tic_tools') . '/css/tic_tools.css',
  );
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
  );

  return $form;
}

function tic_tools_import_dictionary_form_validate(&$form, &$form_state) {
  $letters = array_filter($form_state['values']['letters']);
  if (count($letters) > 5) {
    form_set_error('letters', t('Only import 5 letters at once'));
  }
}

function tic_tools_import_dictionary_form_submit(&$form, &$form_state) {
  $letters = $form_state['values']['letters'];
  variable_set('letters', $letters);
  batch_set(tic_tools_import_dictionary($letters));
}
