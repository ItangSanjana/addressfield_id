<?php

/**
 * @file
 * Province list.
 */

/**
 * Returns addressfield_id_get_administrative_areas().
 */
function addressfield_id_get_administrative_areas() {
  $administrative_areas = drupal_map_assoc(array(
    '',
    t('Bali'),
    t('Bangka Belitung'),
    t('Banten'),
    t('Bengkulu'),
    t('DI Yogyakarta'),
    t('DKI Jakarta'),
    t('Gorontalo'),
    t('Jambi'),
    t('Jawa Barat'),
    t('Jawa Tengah'),
    t('Jawa Timur'),
    t('Kalimantan Barat'),
    t('Kalimantan Selatan'),
    t('Kalimantan Tengah'),
    t('Kalimantan Timur'),
    t('Kalimantan Utara'),
    t('Kepulauan Riau'),
    t('Lampung'),
    t('Maluku'),
    t('Maluku Utara'),
    t('Nanggroe Aceh Darussalam (NAD)'),
    t('Nusa Tenggara Barat (NTB)'),
    t('Nusa Tenggara Timur (NTT)'),
    t('Papua'),
    t('Papua Barat'),
    t('Riau'),
    t('Sulawesi Barat'),
    t('Sulawesi Selatan'),
    t('Sulawesi Tengah'),
    t('Sulawesi Tenggara'),
    t('Sulawesi Utara'),
    t('Sumatera Barat'),
    t('Sumatera Selatan'),
    t('Sumatera Utara'),
  ));

  return $administrative_areas;
}
