<?php

/**
 * @file
 * This module provides definitions for migrations.
 */

/**
 * Implements hook_migrate_api().
 */
function mock_data_migrate_api() {
  $api = array(
    'api' => 2,
    'migrations' => array(
      'MockDataUsers' => array('class_name' => 'MockDataUsersMigration'),
      'MockDataArticles' => array('class_name' => 'MockDataArticlesMigration'),
    ),
  );
  return $api;
}
