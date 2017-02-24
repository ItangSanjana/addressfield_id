<?php

/**
 * @file
 * Handler for Indonesia addresses.
 */

$plugin = array(
  'title' => t('Address form (Indonesia plugin)'),
  'format callback' => 'addressfield_id_addressfield_format_callback',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Implements CALLBACK_addressfield_format_callback().
 */
function addressfield_id_addressfield_format_callback(&$format, $address, $context = array()) {
  module_load_include('inc', 'addressfield_id', 'includes/addressfield_id.locality_block');
  if ($address['country'] == 'ID') {
    if ($context['mode'] == 'form') {
      $settings = $context['instance']['widget']['settings'];
      $administrative_areas = addressfield_id_administrative_area();
      $administrative_area_options =
        array_intersect_key($administrative_areas, $settings['available_administrative_areas']) ?
        array_intersect_key($administrative_areas, $settings['available_administrative_areas']) :
        $administrative_areas;
      $localities = addressfield_id_locality($address['administrative_area']);
      $available_localities = $settings['available_administrative_areas'] ? $settings['available_localities'] : array();
      $locality_options =
        array_intersect_key($localities, $available_localities) ?
        array_intersect_key($localities, $available_localities) :
        $localities;
      $dependent_localities = addressfield_id_dependent_locality($address['administrative_area'], $address['locality']);
      $available_dependent_localities = $available_localities ? $settings['available_dependent_localities'] : array();
      $dependent_locality_options =
        array_intersect_key($dependent_localities, $available_dependent_localities) ?
        array_intersect_key($dependent_localities, $available_dependent_localities) :
        $dependent_localities;
      $format['locality_block']['administrative_area']['#options'] = $administrative_area_options;
      $format['locality_block']['administrative_area']['#weight'] = 0;
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['locality']['#options'] = $locality_options;
      $format['locality_block']['locality']['#empty_value'] = '';
      $format['locality_block']['locality']['#weight'] = 1;
      $format['locality_block']['locality']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['dependent_locality']['#options'] = $dependent_locality_options;
      $format['locality_block']['dependent_locality']['#empty_value'] = '';
      $format['locality_block']['dependent_locality']['#weight'] = 2;
      $format['locality_block']['dependent_locality']['#suffix'] = NULL;
      $format['locality_block']['dependent_locality']['#title'] = t('District/kecamatan');
      $format['locality_block']['postal_code']['#weight'] = 3;
      $format['street_block']['premise']['#description'] = t('Apartment, suite, unit etc. (optional)');
    }
    else {
      $format['locality_block']['dependent_locality']['#suffix'] = ',';
      $format['locality_block']['dependent_locality']['#tag'] = NULL;
      $format['locality_block']['postal_code']['#suffix'] = ',';
    }
  }
  else {
    if (isset($format['locality_block']['administrative_area'])) {
      $format['locality_block']['administrative_area']['#ajax'] = array();
    }
    if (isset($format['locality_block']['locality'])) {
      $format['locality_block']['locality']['#ajax'] = array();
    }
  }
}
