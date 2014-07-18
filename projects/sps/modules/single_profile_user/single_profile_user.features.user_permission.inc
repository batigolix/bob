<?php
/**
 * @file
 * single_profile_user.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function single_profile_user_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'user',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'choose user revisions'.
  $permissions['choose user revisions'] = array(
    'name' => 'choose user revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'delete own user revisions'.
  $permissions['delete own user revisions'] = array(
    'name' => 'delete own user revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'delete user revisions'.
  $permissions['delete user revisions'] = array(
    'name' => 'delete user revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'revert own user revisions'.
  $permissions['revert own user revisions'] = array(
    'name' => 'revert own user revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'revert user revisions'.
  $permissions['revert user revisions'] = array(
    'name' => 'revert user revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'view own user revisions'.
  $permissions['view own user revisions'] = array(
    'name' => 'view own user revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'user_revision',
  );

  // Exported permission: 'view user revisions'.
  $permissions['view user revisions'] = array(
    'name' => 'view user revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'profile_client' => 'profile_client',
    ),
    'module' => 'user_revision',
  );

  return $permissions;
}
