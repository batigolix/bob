<?php
/**
 * @file
 * single_profile_user.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function single_profile_user_user_default_roles() {
  $roles = array();

  // Exported role: profile_client.
  $roles['profile_client'] = array(
    'name' => 'profile_client',
    'weight' => 11,
  );

  return $roles;
}
