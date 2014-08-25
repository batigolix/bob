; single_profile_server make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

projects[ctools][version] = "1.4"
projects[ctools][subdir] = "contrib"

projects[features][version] = "2.0"
projects[features][subdir] = "contrib"

projects[entityreference][version] = "1.1"
projects[entityreference][subdir] = "contrib"

projects[date][version] = "2.8"
projects[date][subdir] = "contrib"

projects[field_group][version] = "1.4"
projects[field_group][subdir] = "contrib"

projects[entity][version] = "1.5"
projects[entity][subdir] = "contrib"

projects[libraries][version] = "2.2"
projects[libraries][subdir] = "contrib"

projects[services][version] = "3.7"
projects[services][subdir] = "contrib"

projects[services_entity][version] = "2.0-alpha7"
projects[services_entity][subdir] = "contrib"

projects[services][version] = "3.7"
projects[services][subdir] = "contrib"

projects[link][version] = "1.2"
projects[link][subdir] = "contrib"

projects[migrate][version] = "2.5"
projects[migrate][subdir] = "contrib"

projects[views][subdir] = "contrib"

projects[user_revision][subdir] = "contrib"
projects[user_revision][version] = "1.7"
projects[user_revision][patch][] = "https://www.drupal.org/files/issues/user_revision-wrong-username-2141157-4.patch"

; +++++ Libraries +++++
