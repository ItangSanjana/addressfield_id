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
function addressfield_id_addressfield_format_callback(
  &$format,
  $address,
  $context = array()
) {
  if ($address['country'] == 'ID') {
    if ($context['mode'] == 'form') {
      $format['locality_block']['administrative_area']['#weight'] = 0;
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['locality']['#options']
      = addressfield_id_locality($address['administrative_area']);
      $format['locality_block']['locality']['#empty_value'] = '';
      $format['locality_block']['locality']['#weight'] = 1;
      $format['locality_block']['locality']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
      $format['locality_block']['dependent_locality']['#options']
      = addressfield_id_dependent_locality(
        $address['administrative_area'],
        $address['locality']
      );
      $format['locality_block']['dependent_locality']['#empty_value'] = '';
      $format['locality_block']['dependent_locality']['#weight'] = 2;
      $format['locality_block']['dependent_locality']['#suffix'] = NULL;
      $format['locality_block']['dependent_locality']['#title'] = t(
        'District/kecamatan'
      );
      $format['locality_block']['postal_code']['#weight'] = 3;
      $format['street_block']['premise']['#description'] = t(
        'Apartment, suite, unit etc. (optional)'
      );
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
