<?php

/**
 * @file
 * This module provides common features for all the migrations. It's always
 * good to have a common base class to structure repeatable elements.
 */

class NewslettersMigration extends XMLMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('XML feed (multi items) of roles (positions)');
    $fields = array(
      'title' => t('Position name'),
    );
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'infsonewsroom:BasicSvId' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );
    $items_url = DRUPAL_ROOT . '/' . drupal_get_path('module', 'single_profile_tools') . '/migrate/rss-service.cfm';
    $item_xpath = '/rss/channel/item';  // relative to document
    $item_ID_xpath = 'infsonewsroom:BasicSvId';         // relative to item_xpath and gets assembled
                                         // into full path /producers/producer/sourceid
    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);
    $this->destination = new MigrateDestinationTerm('newsletters');
    $this->addFieldMapping('name', 'title')        
        ->xpath('title');
    $this->addFieldMapping('description', 'description')
                ->xpath('description');
    $this->addFieldMapping('field_id', 'infsonewsroom:BasicSvId')
                ->xpath('infsonewsroom:BasicSvId');
  }
}
