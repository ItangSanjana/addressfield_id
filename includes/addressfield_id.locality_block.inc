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
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block_list');

  $locality_block = addressfield_id_locality_block();
  $administrative_areas = array_keys($locality_block);
  $administrative_areas = drupal_map_assoc($administrative_areas);

  return $administrative_areas;
}

/**
 * @param $address_administrative_area
 *   Selected administrative area.
 * @return
 *   Locality array.
 */
function addressfield_id_locality($address_administrative_area) {
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block_list');

  $locality_block = addressfield_id_locality_block();
  $localities = array();

  if ($address_administrative_area) {
    foreach ($locality_block as $administrative_area => $locality) {
      $locality = array_keys($locality);
      $localities[$administrative_area] = drupal_map_assoc($locality);
    }

    if (is_array($address_administrative_area)) {
      $localities_array = array();

      foreach ($address_administrative_area as $administrative_area) {
        $localities_array[$administrative_area] = $localities[$administrative_area];
      }

      $localities = $localities_array;
    }
    else {
      $localities = $localities[$address_administrative_area];
    }
  }

  return $localities;
}

/**
 * @param $address_locality
 *   Selected locality.
 * @return
 *   Dependent locality array.
 */
function addressfield_id_dependent_locality($address_locality) {
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block_list');

  $locality_block = addressfield_id_locality_block();
  $dependent_localities = array();

  if ($address_locality) {
    foreach ($locality_block as $administrative_area) {
      foreach ($administrative_area as $locality => $dependent_locality) {
        $dependent_localities[$locality] = drupal_map_assoc($dependent_locality);
      }
    }

    if (is_array($address_locality)) {
      $dependent_localities_array = array();

      foreach ($address_locality as $locality) {
        $dependent_localities_array[$locality] = $dependent_localities[$locality];
      }

      $dependent_localities = $dependent_localities_array;
    }
    else {
      $dependent_localities = $dependent_localities[$address_locality];
    }
  }

  return $dependent_localities;
}
