<?php

/**
 * @file
 * This module provides common features for all the migrations. It's always
 * good to have a common base class to structure repeatable elements.
 */

abstract class MockDataBaseMigration extends Migration {

  /**
   * Defines common elements for migration.
   */
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('mock_data'));
  }

  /**
   * Defines common elements for treating the migration CSV source.
   */
  protected function sourceFileOptions() {
    return array(
      'header_rows' => 1,
      'delimiter' => ";",
      'enclosure' => '"',
    );
  }

}
