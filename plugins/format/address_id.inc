<?php

/**
 * @file
 * A specific handler for Indonesia addresses.
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
  if ($address['country'] == 'ID') {
    if ($context['mode'] == 'form') {
      // Include addressfield_id/addressfield_id.administrative_areas.inc.
      module_load_include('inc', 'addressfield_id', 'addressfield_id.administrative_areas');
      $format['locality_block']['administrative_area']['#options'] = addressfield_id_get_administrative_areas();
      // Include addressfield_id/addressfield_id.localities.inc.
      module_load_include('inc', 'addressfield_id', 'addressfield_id.localities');
      $address_administrative_area = $address['administrative_area'];
      $format['locality_block']['locality']['#options'] = addressfield_id_get_localities($address_administrative_area);
      // Include addressfield_id/addressfield_id.dependent_localities.inc.
      module_load_include('inc', 'addressfield_id', 'addressfield_id.dependent_localities');
      $address_locality = $address['locality'];
      $format['locality_block']['dependent_locality']['#options'] = addressfield_id_get_dependent_localities($address_locality);
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['administrative_area']['#weight'] = 0;
      $format['locality_block']['locality']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['locality']['#weight'] = 0;
      $format['locality_block']['dependent_locality']['#title'] = t('District/kecamatan');
      $format['locality_block']['postal_code']['#weight'] = 0;
      $format['street_block']['premise']['#description'] = t('Apartment, suite, unit etc. (optional)');
    }
    // If context mode is render.
    else {
      $format['locality_block']['postal_code']['#suffix'] = ',';
      $format['locality_block']['postal_code']['#weight'] = 1;
    }
  }
  // Reformat ajax for country outside Indonesia.
  else {
    if (isset($format['locality_block']['administrative_area'])) {
      $format['locality_block']['administrative_area']['#ajax'] = array();
    }
    if (isset($format['locality_block']['locality'])) {
      $format['locality_block']['locality']['#ajax'] = array();
    }
  }
}
