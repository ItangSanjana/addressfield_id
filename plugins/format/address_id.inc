<?php

/**
 * @file
 * A specific handler for Indonesia.
 */

$plugin = array(
  'title' => t('Address form (Indonesia plugin)'),
  'format callback' => 'addressfield_id_addressfield_format_generate',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Implement hook_addressfield_address_formats_alter().
 */
function addressfield_id_addressfield_address_formats_alter(&$address_formats) {
  $address_formats['ID']['required_fields'] = array('locality', 'administrative_area', 'postal_code');
}

/**
 * Format callback Indonesia address.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_id_addressfield_format_generate(&$format, $address, $context = array()) {
  if ($address['country'] == 'ID') {
    module_load_include('inc', 'addressfield_id', 'addressfield_id.administrative_areas');
    $format['locality_block']['administrative_area']['#options'] = addressfield_id_get_administrative_areas();
    module_load_include('inc', 'addressfield_id', 'addressfield_id.localities');
    $format['locality_block']['locality']['#options'] = addressfield_id_get_localities($address['administrative_area']);
    $format['locality_block']['locality']['#render_option_value'] = TRUE;
    $format['locality_block']['postal_code']['#weight'] = 1;
  }
  if ($address['country'] == 'ID' && $context['mode'] == 'form') {
    $format['country']['#weight'] = 0;
    $format['locality_block']['#weight'] = 0;
    $format['locality_block']['administrative_area']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
    );
    $format['locality_block']['administrative_area']['#weight'] = 0;
    $format['street_block']['premise']['#description'] = t('Apartment, suite, unit etc. (optional)');
  }
  else {
    if (isset($format['locality_block']['administrative_area'])) {
      $format['locality_block']['administrative_area']['#ajax'] = array();
    }
  }
}
