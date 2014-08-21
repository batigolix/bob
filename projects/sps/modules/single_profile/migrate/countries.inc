<?php

/**
 * @file
 * Imports countries from a csv file.
 */

class CountriesMigration extends Migration {

  public function __construct() {
    parent::__construct();
    $this->description = t('csv file of countries');
    $this->map = new MigrateSQLMap($this->machineName, array(
      'number' => array(
        'type' => 'int',
        'not null' => TRUE,
      ),
        ), MigrateDestinationTerm::getKeySchema()
    );
    $columns = array(
      1 => array('name', 'Common Name'),
      2 => array('formal_name', 'Formal Name'),
      3 => array('type', 'Type'),
      10 => array('code', 'ISO 3166-1 2 Letter Code'),
      11 => array('code3', 'ISO 3166-1 3 Letter Code'),
      12 => array('number', 'ISO 3166-1 Number'),
    );
    $this->source = new MigrateSourceCSV(
        // Source of the csv is
        // https://commondatastorage.googleapis.com/ckannet-storage/2011-11-25T132653/iso_3166_2_countries.csv
        // todo: fetch this file from the web instead of storing it locally.    
        drupal_get_path('module', 'single_profile') . '/migrate/iso_3166_2_countries.csv', $columns, $this->sourceFileOptions()
    );
    $this->destination = new MigrateDestinationTerm('countries');
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('description', 'formal_name');
    $this->addFieldMapping('field_code', 'code');
    $this->addFieldMapping('field_code3', 'code3');
    $this->addFieldMapping('field_number', 'number');
  }

  /**
   * Defines common elements for treating the migration CSV source.
   */
  protected function sourceFileOptions() {
    return array(
      'header_rows' => 1,
      'delimiter' => ",",
      'enclosure' => '"',
    );
  }

  /**
   * Preprocesses individual field before importing.
   */
  public function prepareRow($row) {
    if ($row->type !== 'Independent State') {
      return FALSE;
    }
  }

}
