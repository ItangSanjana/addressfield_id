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
  $administrative_areas = drupal_map_assoc(array_keys($locality_block));

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
    if (is_array($address_administrative_area)) {
      foreach ($address_administrative_area as $administrative_area) {
        $localities[$administrative_area] = drupal_map_assoc(array_keys($locality_block[$administrative_area]));
      }
      unset ($administrative_area);
    }
    else {
      $localities = drupal_map_assoc(array_keys($locality_block[$address_administrative_area]));
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
function addressfield_id_dependent_locality($address_administrative_area, $address_locality) {
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block_list');
  $locality_block = addressfield_id_locality_block();
  $dependent_localities = array();
  if ($address_administrative_area && $address_locality) {
    if (is_array($address_administrative_area) && is_array($address_locality)) {
      $locality_block_selected = array();
      foreach (array_intersect_key($locality_block, $address_administrative_area) as $administrative_area => $locality) {
          $dependent_localities[$administrative_area] = array_intersect_key($locality, $address_locality);
      }
      unset ($administrative_area, $locality);
    }
    else {
      $dependent_localities =
        $locality_block[$address_administrative_area][$address_locality] ?
        $locality_block[$address_administrative_area][$address_locality] :
        array();
    }
  }

  return $dependent_localities;
}
