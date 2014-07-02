<?php

/**
 * @file
 * Migration class for importing users.
 */

class MockDataUsersMigration extends MockDataBaseMigration {

  /**
   * Migrates users from csv to site.
   */
  public function __construct() {
    parent::__construct();

    $this->description = t('Import users.');

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
        drupal_get_path('module', 'mock_data') . '/data/mock_users.csv', array(), $this->sourceFileOptions()
    );

    // Destination.
    $this->destination = new MigrateDestinationUser();
    $this->addFieldMapping('name', 'nick_name')->dedupe('users', 'name');
    $this->addFieldMapping('mail', 'email')->dedupe('users', 'mail');
    $this->addFieldMapping('pass')->defaultValue(mock_data_generate_random_string(11));
    $this->addFieldMapping('roles')->defaultValue(DRUPAL_AUTHENTICATED_RID);
    $this->addFieldMapping('field_last_name', 'last_name');
    $this->addFieldMapping('field_first_name', 'first_name');
    $this->addFieldMapping('field_gender', 'gender');
    $this->addFieldMapping('field_country', 'country');
    $this->addFieldMapping('status')->defaultValue(1);
        // Taxonomy Term. Allow multiple.
    $this->addFieldMapping('field_newsletter_subscriptions', 'newsletter_ids');
  }

  /**
   * Preprocesses individual field before importing.
   */
  public function prepareRow($row) {
    $row->nick_name = mock_data_slugify($row->nick_name);
    $newsletters = explode('|', $row->newsletters);
    foreach($newsletters as $newsletter) {
      $row->newsletter_ids[] = single_profile_tools_entity_id_from_field_value('taxonomy_term', 'newsletters', 'field_id', $newsletter);
    }
    $row->country = single_profile_tools_entity_id_from_field_value('taxonomy_term', 'countries', 'field_code', $row->country);
  }

}
