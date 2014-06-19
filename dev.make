; ----------------
; Generated makefile from http://drushmake.me
; Permanent URL: http://drushmake.me/file.php?token=a47bca4bae6b
; ----------------
;
; This is a working makefile - try it! Any line starting with a `;` is a comment.
  
; Core version
; ------------
; Each makefile should begin by declaring the core version of Drupal that all
; projects should be compatible with.
  
core = 7.x
  
; API version
; ------------
; Every makefile needs to declare its Drush Make API version. This version of
; drush make uses API version `2`.
  
api = 2
    
; Modules
; --------

projects[devel][type] = "module"
projects[devel][subdir] = "development"

projects[environment_indicator][type] = "module"
projects[environment_indicator][subdir] = "development"
  
projects[coffee][type] = "module"
projects[coffee][subdir] = "development"

projects[stage_file_proxy][type] = "module"
projects[stage_file_proxy][subdir] = "development"

; Themes
; --------
projects[] = shiny


  
  
; Libraries
; ---------
; No libraries were included

