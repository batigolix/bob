<?php

/**
 * @file
 * Contains forms for the Single profile tools module.
 */

/**
 * Constructs settings form.
 */
function single_profile_settings($form, &$form_state) {
  $form = array();
  
  $values = variable_get('clients');
  $num_clients = !empty($values['num_clients']) ? $values['num_clients'] : 3;

  $form['clients'] = array(
    '#type' => 'fieldset',
    '#title' => 'Clients',
    '#tree' => TRUE,
  );

  // Allows defining the amount of clients. Very poor mans implementation of
  // adding dynamically multiple fieldsets
  $form['clients']['num_clients'] = array(
    '#type' => 'textfield',
    '#title' => 'Number of clients',
    '#size' => 3,
    '#tree' => TRUE,
    '#default_value' => $num_clients,
  );

  // Fieldset with settings per client.
  for ($i = 0; $i < $num_clients; $i++) {

    $form['clients']['client'][$i]['header'] = array(
      '#markup' => t('<h4>Client !i</h4>', array('!i' => $i + 1)),
    );

    $form['clients']['client'][$i]['uri'] = array(
      '#title' => t('URI'),
      '#type' => 'textfield',
      '#size' => 32,
      '#default_value' => !empty($values['client'][$i]['uri']) ? $values['client'][$i]['uri'] : NULL,
    );

    $form['clients']['client'][$i]['name'] = array(
      '#title' => t('Name'),
      '#type' => 'textfield',
      '#size' => 24,
      '#default_value' => !empty($values['client'][$i]['name']) ? $values['client'][$i]['name'] : NULL,
    );

    // Links a client with a user for authenticationa and revisioning.
    $form['clients']['client'][$i]['user'] = array(
      '#type' => 'textfield',
      '#title' => t('User'),
      '#size' => 24,
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => !empty($values['client'][$i]['user']) ? $values['client'][$i]['user'] : NULL,
    );
    
    // Aah the beauty of old skool HTML elements.
    $form['clients']['client'][$i]['footer'] = array(
      '#markup' => '<hr />',
    );
  }

  return system_settings_form($form);
}

/**
 * Validates single_profile_settings form.
 * Checks is a user is assigned to multiple account which is an issue.
 */
function single_profile_settings_validate($form, $form_state) {
  dpm($form_state['values']);
  $users_values = array();

  foreach ($form_state['values']['clients']['client'] as $client) {
    if (isset($client['user'])) {
      $users_values[] = $client['user'];
    }
  }

  if (_array_has_dupes($users_values)) {
    form_set_error('clients', t('A user can only be associated with one client. Please change the user'));
  }
}

/**
 * Checks for duplicate values inside an array.
 */
function _array_has_dupes($array) {
  return count($array) !== count(array_unique($array));
}
