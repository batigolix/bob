<?php
/**
 * @file
 * single_profile.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function single_profile_taxonomy_default_vocabularies() {
  return array(
    'newsletters' => array(
      'name' => 'Newsletters',
      'machine_name' => 'newsletters',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
