# Address Field ID

This module integrates Indonesia address format with [Drupal](//drupal.org) [Address Field](//drupal.org/project/addressfield).

## Requirement

- [Address Field](//drupal.org/project/addressfield)

## Installation

- Using [drush](https://github.com/drush-ops/drush)
```Shell
cd to/your/drupal/project
drush dl addressfield_id
drush en addressfield_id
```
- Manual install [Installing modules (Drupal 7)](https://www.drupal.org/documentation/install/modules-themes/modules-7).

## Configuration

- Enable [Address Field](//drupal.org/project/addressfield) field.
```Shell
admin/structure/types/manage/[your_content_type]/fields
```
- Enable Address Field ID format handlers.
```Shell
admin/structure/types/manage/[your_content_type]/fields/[your_address_field]
```
