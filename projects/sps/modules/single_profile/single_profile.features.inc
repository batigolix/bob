<?php
/**
 * @file
 * single_profile.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function single_profile_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
