# Address Field ID

## Introduction

This module integrates Indonesia addresses with [Address Field](//drupal.org/project/addressfield).

## Requirement

- [Address Field](//drupal.org/project/addressfield)

## Installation

- Using [drush](https://github.com/drush-ops/drush)

  ```Shell
  cd to/your/drupal/project
  drush dl addressfield_id
  drush en addressfield_id
  ```

- or manual install see: [Installing modules (Drupal 7)](https://www.drupal.org/documentation/install/modules-themes/modules-7).

## Configuration

- Add Address Field field see: [Address Fild doc](https://www.drupal.org/node/1267280)
- Enable Address Field ID format handlers e.g. go to:

  ```Shell
  admin/structure/types/manage/[content_type]/fields/[addressfield_field]
  ```
