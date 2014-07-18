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

  $values = variable_get('clients');
  //dpm($values);
  $num_clients = !empty($values['num_clients']) ? $values['num_clients'] : 3;

  $form['clients'] = array(
    '#type' => 'fieldset',
    '#title' => 'Clients',
    '#tree' => TRUE,
  );

  $form['clients']['num_clients'] = array(
    '#type' => 'textfield',
    '#title' => 'Number of clients',
    '#size' => 3,
    '#tree' => TRUE,
    '#default_value' => $num_clients,
  );

  for ($i = 0; $i < $num_clients; $i++) {
//    $form['clients'][$i] = array(
//      '#type' => 'container',
//      '#attributes' => array('class' => array('client-container')),
//    );

    $form['clients'][$i]['header'] = array(
      '#markup' => t('<h4>Client !i</h4>', array('!i' => $i + 1)),
    );

    $form['clients'][$i]['uri'] = array(
      '#title' => t('URI'),
      '#type' => 'textfield',
      '#size' => 32,
      '#default_value' => !empty($values[$i]['uri']) ? $values[$i]['uri'] : NULL,
    );
    $form['clients'][$i]['name'] = array(
      '#title' => t('Name'),
      '#type' => 'textfield',
      '#size' => 24,
      '#default_value' => !empty($values[$i]['name']) ? $values[$i]['name'] : NULL,
    );

    $form['clients'][$i]['user'] = array(
      '#type' => 'textfield',
      '#title' => t('User'),
      '#size' => 24,
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => !empty($values[$i]['user']) ? $values[$i]['user'] : NULL,
    );
    $form['clients'][$i]['footer'] = array(
      '#markup' => '<hr />',
    );
  }

  return system_settings_form($form);
}
