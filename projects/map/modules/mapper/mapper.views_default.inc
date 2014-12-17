<?php
/**
 * @file
 * mapper.views_default.inc
 * Contains views.
 */

/**
 * Implements hook_views_default_views().
 */
function tic_views_default_viewsss() {
// Add view to list of views to provide.
  $views[$view->name] = $view;
// At the end, return array of default views.
  return $views;
}
/**
 * Implementation of hook_views_default_views().
 **/
function tic_views_default_views() {
//  $files = file_scan_directory(drupal_get_path('module', 'mapper'). '/views', '.view');
  $files = file_scan_directory(drupal_get_path('module', 'mapper'). '/views', '/.*\.view$/');
  dd($files);
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }
  return $views;
}