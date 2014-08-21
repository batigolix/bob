<?php

/**
 * @file
 * Imports newsletters from an xml file.
 */
class NewslettersMigration extends XMLMigration {

  public function __construct() {
    parent::__construct();
    $this->description = t('XML feed (multi items) of roles (positions)');
    $fields = array(
      'title' => t('Position name'),
    );
    $this->map = new MigrateSQLMap($this->machineName, array(
      'infsonewsroom:BasicSvId' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      )
        ), MigrateDestinationTerm::getKeySchema()
    );

    // Original rss feed can be found on 
    // http://ec.europa.eu/information_society/newsroom/cf/dae/rss-service.cfm
    // Todo: find way fetching this online, without storing locally first.
    $items_url = DRUPAL_ROOT . '/' . drupal_get_path('module', 'single_profile') . '/migrate/rss-service.cfm';
    $item_xpath = '/rss/channel/item';
    $item_ID_xpath = 'infsonewsroom:BasicSvId';
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
