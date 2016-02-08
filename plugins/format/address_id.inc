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
 * Implements hook_addressfield_address_formats_alter().
 */
function addressfield_id_addressfield_address_formats_alter(&$address_formats) {
  $address_formats['ID']['used_fields'][] = 'dependent_locality';
  $address_formats['ID']['required_fields'] = array(
    'administrative_area',
    'locality',
    'dependent_locality',
    'postal_code',
  );
}

/**
 * Implements CALLBACK_addressfield_format_callback().
 */
function addressfield_id_addressfield_format_callback(&$format, $address, $context = array()) {
  // Include addressfield_id/addressfield_id.locality_block.inc.
  module_load_include('inc', 'addressfield_id', 'addressfield_id.locality_block');

  if ($address['country'] == 'ID') {
    if ($context['mode'] == 'form') {
      $settings = $context['instance']['widget']['settings'];
      $available_administrative_areas = $settings['available_administrative_areas'];
      $available_localities = $settings['available_localities'];
      $available_dependent_localities = $settings['available_dependent_localities'];
      $administrative_area_options = addressfield_id_administrative_area();
      $locality_options = addressfield_id_locality($address['administrative_area']);
      $dependent_locality_options = addressfield_id_dependent_locality($address['locality']);

      // Computes the intersection of each options according it's availablity
      // using keys for comparison so we can build new options.
      if ($available_administrative_areas) {
        $administrative_area_options = array_intersect_key($administrative_area_options, $available_administrative_areas);
      }
      if ($available_localities) {
        $locality_options = array_intersect_key($locality_options, $available_localities);
      }
      if ($available_dependent_localities) {
        $dependent_locality_options = array_intersect_key($dependent_locality_options, $available_dependent_localities);
      }

      $format['locality_block']['administrative_area']['#options'] = $administrative_area_options;
      $format['locality_block']['administrative_area']['#weight'] = 0;
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );

      $format['locality_block']['locality']['#options'] = $locality_options;
      $format['locality_block']['locality']['#empty_value'] = '';
      $format['locality_block']['locality']['#weight'] = 0;
      $format['locality_block']['locality']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );

      $format['locality_block']['dependent_locality']['#options'] = $dependent_locality_options;
      $format['locality_block']['dependent_locality']['#empty_value'] = '';
      $format['locality_block']['dependent_locality']['#suffix'] = NULL;
      $format['locality_block']['dependent_locality']['#title'] = t('District/kecamatan');

      $format['street_block']['premise']['#description'] = t('Apartment, suite, unit etc. (optional)');
    }
    // If context mode is render.
    else {
      $format['locality_block']['dependent_locality']['#suffix'] = ',';
      $format['locality_block']['dependent_locality']['#tag'] = NULL;
      $format['locality_block']['postal_code']['#suffix'] = ',';
      $format['locality_block']['postal_code']['#weight'] = 1;
    }
  }
  // Cancel the AJAX for forms we don't control.
  else {
    if (isset($format['locality_block']['administrative_area'])) {
      $format['locality_block']['administrative_area']['#ajax'] = array();
    }
    if (isset($format['locality_block']['locality'])) {
      $format['locality_block']['locality']['#ajax'] = array();
    }
  }
}
