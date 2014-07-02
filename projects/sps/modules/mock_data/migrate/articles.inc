<?php

/**
 * @file
 * Migration class for importing articles.
 */

class MockDataArticlesMigration extends MockDataBaseMigration {

  /**
   * Migrates articles from csv to site.
   */
  public function __construct() {
    parent::__construct();

    $this->description = t('Import articles.');

    // Dependencies, so we migrate in order.
    $this->dependencies = array('MockDataUsers');

    // Create a map object for tracking the relationships between source rows.
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'int',
        'not null' => TRUE,
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(
        drupal_get_path('module', 'mock_data') . '/data/mock_content.csv', array(), $this->sourceFileOptions()
    );

    // Define destination.
    $this->destination = new MigrateDestinationNode('article', array(
      'text_format' => 'full_html',
      'language' => 'en'));

    // Link with users, based on the ID.
    $this->addFieldMapping('uid', 'author')
        ->sourceMigration('MockDataUsers');

    // Title.
    $this->addFieldMapping('title', 'title');

    // Teaser.
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('created')->defaultValue(REQUEST_TIME);
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('promote', 'promote');

    // Image.
    $this->addFieldMapping('field_image', 'picture');
    $this->addFieldMapping('field_image:file_replace')
        ->defaultValue(FILE_EXISTS_REPLACE);
    $this->addFieldMapping('field_image:source_dir')
        ->defaultValue(drupal_get_path('module', 'mock_data') . '/data');

    // Taxonomy Term. Allow multiple.
    $this->addFieldMapping('field_tags', 'tag 1')
        ->separator(' ');
    $this->addFieldMapping('field_tags:create_term')
        ->defaultValue(TRUE);
  }

  /**
   * Preprocesses individual field before importing.
   */
  public function prepareRow($row) {
    $row->title = ucwords($row->title);
  }

}
