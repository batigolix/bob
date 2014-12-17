<?php

/**
 * @file
 * Migrate definitions for the Veldeke dictionary.
 */


/**
 * Defines a dynamic migration that is reused for each source CSV file.
 */
class TicMigration extends DynamicMigration {

  /**
   * Constructs the migration.
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Import nuts from CSV file.');

    // Creates a map object for tracking the relationships between source rows.
    $this->map = new MigrateSQLMap($this->machineName, array(
        'code' => array(
          'type' => 'int',
          'length' => 24,
          'not null' => TRUE,
          'description' => 'Code',
        ),
      ), MigrateDestinationNode::getKeySchema()
    );

//    // Creates a source object that contains the data.
//    if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
//      $realpath = $wrapper->realpath();
//    }

//    $path = drupal_get_path('module', 'mapper');


    $this->path = drupal_get_path('module', 'mapper') . '/nuts.csv';

    // D0S2UNIX
//    $file = file_get_contents($this->path);
//    $file = str_replace("\r", "", $file);
//    file_put_contents($this->path, $file);

//    dd($this->csvcolumns());

    $this->source = new MigrateSourceCSV($this->path, $this->csvcolumns(), array(

      'header_rows' => 1,
      'delimiter' => ',',
      'enclosure' => '"',
//      'embedded_newlines' => TRUE,
    ));

//    dd($this->source);

    // Creates a destination object that receives the data.
    $this->destination = new MigrateDestinationTerm('nuts_regions');

    $this->addFieldMapping('name', 'description')->description('Title');
    $this->addFieldMapping('nuts_level', 'level');
    $this->addFieldMapping('nuts_remark', 'remark');
    $this->addFieldMapping('nuts_id', 'code');
    $this->addFieldMapping('nuts_code', 'nuts_code');
    $this->addFieldMapping('nuts_description', 'description');

    $this->addFieldMapping('parent', 'parent_id');

    // Defines unmapped destination fields.
    $this->addFieldMapping('description')->issueGroup(t('DNM'));
    $this->addFieldMapping('format')->issueGroup(t('DNM'));
    $this->addFieldMapping('path')->issueGroup(t('DNM'));
    $this->addFieldMapping('weight')->issueGroup(t('DNM'));

  }

  /**
   * Assigns csv column data to key.
   */
  function csvcolumns() {

//    dd($columns);

    $columns[0] = array('level', 'Level');
    $columns[1] = array('code', 'Code');
    $columns[2] = array('nuts_code', 'NUTS-Code');
    $columns[3] = array('description', 'Description');
    $columns[4] = array('remark', 'Remark');
    return $columns;
  }

  /**
   * Prepares rows before import.
   */
  function prepareRow($row) {
    //    $row->first_char_head_word = strtolower(_remove_accents($row->head_word));
//    $row->first_char_head_word = $row->first_char_head_word[0];
//    $row->first_char_translation = strtolower(_remove_accents($row->translation));
//    $row->first_char_translation = $row->first_char_translation[0];

//    substr("a,b,c,d,e,", 0, -1)
    $this->nuts_code_2 = substr($row->nuts_code, 0, -1);
//dd($this->nuts_code_2);
//    dd($row->description);
//
//
////    $source_id = $this->findReferencedNid($row->body);
//
//    if(strlen($this->nuts_code_2)>=2) {
//
//      $row->parent_id = $this->handleSourceMigration('Tic', $this->nuts_code_2);
//    }
//    else {
//      $row->parent_id = 0;
//    }
//
//    dd($row->parent_id);
//

    $source_id = $this->findReferencedTid($row->nuts_code);
    $row->parent_id = $this->handleSourceMigration('Tic', $source_id);

  }

  protected function findReferencedTid($id) {
//dd($id);
   // dd($this->source);
  }


  protected function createStub($migration, array $source_id) {
//dd('test');
//    echo 'asjfklas';
//    dd($source_id);
    $term = new stdClass();
    $term->name = t('Stub for term @id', array('@id' => $source_id[0]));
    $term->vocabulary = 'team';
$term->vocabulary_machine_name = $this->destination->getBundle();
    taxonomy_term_save($term);
    if (isset($term->tid)) {
      return array($term->tid);
    }
    else {
      return FALSE;
    }

  }


}

function reunite_nuts_regions() {
//  $wrentry = entity_metadata_wrapper('node', $entry);
//




}


/**
 * Inspects wrapped entity fields.
 */
function _wwrapper_debug($w) {
  $values = array();
  foreach ($w->getPropertyInfo() as $key => $val) {
    $values[$key] = $w->$key->value();
  }
  return $values;
}

