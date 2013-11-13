<?php

/**
 * @file
 * A specific handler for Indonesia.
 */

$plugin = array(
  'title' => t('Address form (ID add-on)'),
  'format callback' => 'addressfield_id_format_address_generate',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Format callback Indonesia address.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_id_format_address_generate(&$format, $address, $context = array()) {
  // Format form.
  if ($address['country'] == 'ID' && $context['mode'] == 'form') {
    // Rearrange fields.
    $format['locality_block']['#weight'] = -9;
    $format['locality_block']['administrative_area']['#weight'] = 0;
    $format['locality_block']['locality']['#weight'] = 1;
    $format['locality_block']['postal_code']['#weight'] = 2;
  }
  // Format render.
  if ($context['mode'] == 'render') {
    // Render option value.
    $format['locality_block']['administrative_area']['#prefix'] = ', ';
    $format['locality_block']['administrative_area']['#render_option_value'] = TRUE;
  }
  // Test if country is Indonesia.
  if ($address['country'] == 'ID') {
    // List administrative divisions 'Code => Name'.
    $format['locality_block']['administrative_area']['#options'] = array(
      ''   => t('--'),
      '51' => t('Bali'),
      '36' => t('Banten'),
      '17' => t('Bengkulu'),
      '75' => t('Gorontalo'),
      '31' => t('Jakarta DKI'),
      '15' => t('Jambi'),
      '32' => t('Jawa Barat'),
      '33' => t('Jawa Tengah'),
      '35' => t('Jawa Timur'),
      '61' => t('Kalimantan Barat'),
      '63' => t('Kalimantan Selatan'),
      '62' => t('Kalimantan Tengah'),
      '64' => t('Kalimantan Timur'),
      '65' => t('Kalimantan Utara'),
      '19' => t('Kepulauan Bangka Belitung'),
      '21' => t('Kepulauan Riau'),
      '18' => t('Lampung'),
      '81' => t('Maluku'),
      '82' => t('Maluku Utara'),
      '11' => t('Nanggroe Aceh Darussalam'),
      '52' => t('Nusa Tenggara Barat'),
      '53' => t('Nusa Tenggara Timur'),
      '91' => t('Papua'),
      '92' => t('Papua Barat'),
      '14' => t('Riau'),
      '76' => t('Sulawesi Barat'),
      '73' => t('Sulawesi Selatan'),
      '72' => t('Sulawesi Tengah'),
      '74' => t('Sulawesi Tenggara'),
      '71' => t('Sulawesi Utara'),
      '13' => t('Sumatera Barat'),
      '16' => t('Sumatera Selatan'),
      '12' => t('Sumatera Utara'),
      '34' => t('Yogyakarta DI'),
    );
    // Replace title.
    $format['locality_block']['locality']['#title'] = t('Regency/City');
    $format['locality_block']['administrative_area']['#title'] = t('Province');
  }
}
