<?php

/**
 * @file
 * A list of all administrative areas.
 */

/**
 * @return
 *   Administrative area array.
 */
function addressfield_id_administrative_area() {
  module_load_include(
    'inc',
    'addressfield_id',
    'includes/addressfield_id.locality_block_list'
  );
  $locality_block = array_keys(addressfield_id_locality_block());
  $administrative_areas = drupal_map_assoc($locality_block);

  return $administrative_areas;
}

/**
 * @param $aa
 *   Selected administrative area.
 * @return
 *   Locality array.
 */
function addressfield_id_locality($administrative_area) {
  module_load_include(
    'inc',
    'addressfield_id',
    'includes/addressfield_id.locality_block_list'
  );
  $locality_block = addressfield_id_locality_block();
  $localities = array();
  if ($administrative_area) {
    $localities = drupal_map_assoc(array_keys(
      $locality_block[$administrative_area]
    ));
  }

  return $localities;
}

/**
 * @param $address_locality
 *   Selected locality.
 * @return
 *   Dependent locality array.
 */
function addressfield_id_dependent_locality($administrative_area, $locality) {
  module_load_include(
    'inc',
    'addressfield_id',
    'includes/addressfield_id.locality_block_list'
  );
  $locality_block = addressfield_id_locality_block();
  $dependent_localities = array();
  if ($administrative_area && $locality) {
      $dependent_localities = $locality_block[$administrative_area][$locality];
  }

  return $dependent_localities;
}
