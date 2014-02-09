<?php

/**
 * @file
 * A specific handler for Indonesia.
 */

$plugin = array(
  'title' => t('Address form (Indonesia add-on)'),
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
  if ($address['country'] == 'ID') {
    $format['locality_block']['administrative_area']['#options'] = _addressfield_id_administrative_area_options_list();
    $format['locality_block']['locality']['#options'] = _addressfield_id_locality_options_list($address['administrative_area']);
    $format['locality_block']['administrative_area']['#title'] = t('Province');
    $format['locality_block']['locality']['#title'] = t('City/Regency');

    if ($context['mode'] == 'render') {
      $format['locality_block']['administrative_area']['#prefix'] = ', ';
    }

    if ($context['mode'] == 'form' && $address['country'] == 'ID') {
      $format['locality_block']['locality']['#weight'] = 1;
      $format['locality_block']['postal_code']['#weight'] = 2;
      $format['locality_block']['locality']['#process'][] = 'addressfield_id_format_address_process';
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
      );
    }
    else {
      if (isset($format['locality_block']['administrative_area'])) {
        $format['locality_block']['administrative_area']['#ajax'] = array();
      }
    }
  }
}

/**
 * Don't validate any element we don't control.
 */
function addressfield_id_format_address_process($element) {
  $element['#limit_validation_errors'] = array($element['#parents']);

  return $element;
}

/**
 * Administrative area.
 */
function _addressfield_id_administrative_area_options_list() {
  return array(
    '' => t('--'),
    'Bali' => t('Bali'),
    'Banten' => t('Banten'),
    'Bengkulu' => t('Bengkulu'),
    'Gorontalo' => t('Gorontalo'),
    'Jakarta DKI' => t('Jakarta DKI'),
    'Jambi' => t('Jambi'),
    'Jawa Barat' => t('Jawa Barat'),
    'Jawa Tengah' => t('Jawa Tengah'),
    'Jawa Timur' => t('Jawa Timur'),
    'Kalimantan Barat' => t('Kalimantan Barat'),
    'Kalimantan Selatan' => t('Kalimantan Selatan'),
    'Kalimantan Tengah' => t('Kalimantan Tengah'),
    'Kalimantan Timur' => t('Kalimantan Timur'),
    'Kalimantan Utara' => t('Kalimantan Utara'),
    'Kepulauan Bangka Belitung' => t('Kepulauan Bangka Belitung'),
    'Kepulauan Riau' => t('Kepulauan Riau'),
    'Lampung' => t('Lampung'),
    'Maluku' => t('Maluku'),
    'Maluku Utara' => t('Maluku Utara'),
    'Nanggroe Aceh Darussalam' => t('Nanggroe Aceh Darussalam'),
    'Nusa Tenggara Barat' => t('Nusa Tenggara Barat'),
    'Nusa Tenggara Timur' => t('Nusa Tenggara Timur'),
    'Papua' => t('Papua'),
    'Papua Barat' => t('Papua Barat'),
    'Riau' => t('Riau'),
    'Sulawesi Barat' => t('Sulawesi Barat'),
    'Sulawesi Selatan' => t('Sulawesi Selatan'),
    'Sulawesi Tengah' => t('Sulawesi Tengah'),
    'Sulawesi Tenggara' => t('Sulawesi Tenggara'),
    'Sulawesi Utara' => t('Sulawesi Utara'),
    'Sumatera Barat' => t('Sumatera Barat'),
    'Sumatera Selatan' => t('Sumatera Selatan'),
    'Sumatera Utara' => t('Sumatera Utara'),
    'Yogyakarta DI' => t('Yogyakarta DI'),
  );
}

/**
 * Locality.
 */
function _addressfield_id_locality_options_list($locality) {
  $administrative_area = _addressfield_id_administrative_area_options_list();
  switch (array_search($locality, $administrative_area)) {
    case 'Bali':
      return drupal_map_assoc(array(
        t('Badung'),
        t('Bangli'),
        t('Buleleng'),
        t('Denpasar'),
        t('Gianyar'),
        t('Jembrana'),
        t('Karangasem'),
        t('Klungkung'),
        t('Tabanan'),
      ));
      break;

    case 'Banten':
      return drupal_map_assoc(array(
        t('Cilegon'),
        t('Lebak'),
        t('Pandeglang'),
        t('Serang (Kab.)'),
        t('Serang (Kota)'),
        t('Tangerang (Kab.)'),
        t('Tangerang (Kota)'),
        t('Tangerang Selatan'),
      ));
      break;

    case 'Bengkulu':
      return drupal_map_assoc(array(
        t('Bengkulu'),
        t('Bengkulu Selatan'),
        t('Bengkulu Tengah'),
        t('Bengkulu Utara'),
        t('Kaur'),
        t('Kepahiang'),
        t('Lebong'),
        t('Muko Muko'),
        t('Rejang Lebong'),
        t('Seluma'),
      ));
      break;

    case 'Gorontalo':
      return drupal_map_assoc(array(
        t('Boalemo'),
        t('Bone Bolango'),
        t('Gorontalo (Kab.)'),
        t('Gorontalo (Kota)'),
        t('Gorontalo Utara'),
        t('Pohuwato'),
      ));
      break;

    case 'Jakarta DKI':
      return drupal_map_assoc(array(
        t('Jakarta Barat'),
        t('Jakarta Pusat'),
        t('Jakarta Selatan'),
        t('Jakarta Timur'),
        t('Jakarta Utara'),
        t('Kepulauan Seribu'),
      ));
      break;

    case 'Jambi':
      return drupal_map_assoc(array(
        t('Batang Hari'),
        t('Bungo'),
        t('Jambi'),
        t('Kerinci'),
        t('Merangin'),
        t('Muaro Jambi'),
        t('Sarolangun'),
        t('Sungaipenuh'),
        t('Tanjung Jabung Barat'),
        t('Tanjung Jabung Timur'),
        t('Tebo'),
      ));
      break;

    case 'Jawa Barat':
      return drupal_map_assoc(array(
        t('Bandung (kab.)'),
        t('Bandung (Kota)'),
        t('Bandung Barat'),
        t('Banjar'),
        t('Bekasi (kab.)'),
        t('Bekasi (Kota)'),
        t('Bogor (kab.)'),
        t('Bogor (Kota)'),
        t('Ciamis'),
        t('Cianjur'),
        t('Cimahi'),
        t('Cirebon (kab.)'),
        t('Cirebon (Kota)'),
        t('Depok'),
        t('Garut'),
        t('Indramayu'),
        t('Karawang'),
        t('Kuningan'),
        t('Majalengka'),
        t('Pangandaran'),
        t('Purwakarta'),
        t('Subang'),
        t('Sukabumi (kab.)'),
        t('Sukabumi (Kota)'),
        t('Sumedang'),
        t('Tasikmalaya (kab.)'),
        t('Tasikmalaya (Kota)'),
      ));
      break;

    case 'Jawa Tengah':
      return drupal_map_assoc(array(
        t('Banjarnegara'),
        t('Banyumas'),
        t('Batang'),
        t('Blora'),
        t('Boyolali'),
        t('Brebes'),
        t('Cilacap'),
        t('Demak'),
        t('Grobogan'),
        t('Jepara'),
        t('Karanganyar'),
        t('Kebumen'),
        t('Kendal'),
        t('Klaten'),
        t('Kudus'),
        t('Magelang (Kab.)'),
        t('Magelang (Kota)'),
        t('Pati'),
        t('Pekalongan (Kab.)'),
        t('Pekalongan (Kota)'),
        t('Pemalang'),
        t('Purbalingga'),
        t('Purworejo'),
        t('Rembang'),
        t('Salatiga'),
        t('Semarang (Kab.)'),
        t('Semarang (Kota)'),
        t('Sragen'),
        t('Sukoharjo'),
        t('Surakarta (Solo)'),
        t('Tegal (Kab.)'),
        t('Tegal (Kota)'),
        t('Temanggung'),
        t('Wonogiri'),
        t('Wonosobo'),
      ));
      break;

    case 'Jawa Timur':
      return drupal_map_assoc(array(
        t('Bangkalan'),
        t('Banyuwangi'),
        t('Batu'),
        t('Blitar (Kab.)'),
        t('Blitar (Kota)'),
        t('Bojonegoro'),
        t('Bondowoso'),
        t('Gresik'),
        t('Jember'),
        t('Jombang'),
        t('Kediri (Kab.)'),
        t('Kediri (Kota)'),
        t('Lamongan'),
        t('Lumajang'),
        t('Madiun (Kab.)'),
        t('Madiun (Kota)'),
        t('Magetan'),
        t('Malang (Kab.)'),
        t('Malang (Kota)'),
        t('Mojokerto (Kab.)'),
        t('Mojokerto (Kota)'),
        t('Nganjuk'),
        t('Ngawi'),
        t('Pacitan'),
        t('Pamekasan'),
        t('Pasuruan (Kab.)'),
        t('Pasuruan (Kota)'),
        t('Ponorogo'),
        t('Probolinggo (Kab.)'),
        t('Probolinggo (Kota)'),
        t('Sampang'),
        t('Sidoarjo'),
        t('Situbondo'),
        t('Sumenep'),
        t('Surabaya'),
        t('Trenggalek'),
        t('Tuban'),
        t('Tulungagung'),
      ));
      break;

    case 'Kalimantan Barat':
      return drupal_map_assoc(array(
        t('Bengkayang'),
        t('Kapuas Hulu'),
        t('Kayong Utara'),
        t('Ketapang'),
        t('Kubu Raya'),
        t('Landak'),
        t('Melawi'),
        t('Pontianak (Kab.)'),
        t('Pontianak (Kota)'),
        t('Sambas'),
        t('Sanggau'),
        t('Sekadau'),
        t('Singkawang'),
        t('Sintang'),
      ));
      break;

    case 'Kalimantan Selatan':
      return drupal_map_assoc(array(
        t('Balangan'),
        t('Banjar'),
        t('Banjarbaru'),
        t('Banjarmasin'),
        t('Barito Kuala'),
        t('Hulu Sungai Selatan'),
        t('Hulu Sungai Tengah'),
        t('Hulu Sungai Utara'),
        t('Kotabaru'),
        t('Tabalong'),
        t('Tanah Bumbu'),
        t('Tanah Laut'),
        t('Tapin'),
      ));
      break;

    case 'Kalimantan Tengah':
      return drupal_map_assoc(array(
        t('Barito Selatan'),
        t('Barito Timur'),
        t('Barito Utara'),
        t('Gunung Mas'),
        t('Kapuas'),
        t('Katingan'),
        t('Kotawaringin Barat'),
        t('Kotawaringin Timur'),
        t('Lamandau'),
        t('Murung Raya'),
        t('Palangka Raya'),
        t('Pulang Pisau'),
        t('Seruyan'),
        t('Sukamara'),
      ));
      break;

    case 'Kalimantan Timur':
      return drupal_map_assoc(array(
        t('Balikpapan'),
        t('Berau'),
        t('Bontang'),
        t('Kutai Barat'),
        t('Kutai Kartanegara'),
        t('Kutai Timur'),
        t('Paser'),
        t('Penajam Paser Utara'),
        t('Samarinda'),
      ));
      break;

    case 'Kalimantan Utara':
      return drupal_map_assoc(array(
        t('Bulungan (Bulongan)'),
        t('Malinau'),
        t('Nunukan'),
        t('Tana Tidung'),
        t('Tarakan'),
      ));
      break;

    case 'Kepulauan Bangka Belitung':
      return drupal_map_assoc(array(
        t('Bangka'),
        t('Bangka Barat'),
        t('Bangka Selatan'),
        t('Bangka Tengah'),
        t('Belitung'),
        t('Belitung Timur'),
        t('Pangkal Pinang'),
      ));
      break;

    case 'Kepulauan Riau':
      return drupal_map_assoc(array(
        t('Batam'),
        t('Bintan'),
        t('Karimun'),
        t('Kepulauan Anambas'),
        t('Lingga'),
        t('Natuna'),
        t('Tanjung Pinang'),
      ));
      break;

    case 'Lampung':
      return drupal_map_assoc(array(
        t('Bandar Lampung'),
        t('Lampung Barat'),
        t('Lampung Selatan'),
        t('Lampung Tengah'),
        t('Lampung Timur'),
        t('Lampung Utara'),
        t('Mesuji'),
        t('Metro'),
        t('Pesawaran'),
        t('Pesisir Barat'),
        t('Pringsewu'),
        t('Tanggamus'),
        t('Tulang Bawang'),
        t('Tulang Bawang Barat'),
        t('Way Kanan'),
      ));
      break;

    case 'Maluku':
      return drupal_map_assoc(array(
        t('Ambon'),
        t('Buru'),
        t('Buru Selatan'),
        t('Kepulauan Aru'),
        t('Maluku Barat Daya'),
        t('Maluku Tengah'),
        t('Maluku Tenggara'),
        t('Maluku Tenggara Barat'),
        t('Seram Bagian Barat'),
        t('Seram Bagian Timur'),
        t('Tual'),
      ));
      break;

    case 'Maluku Utara':
      return drupal_map_assoc(array(
        t('Halmahera Barat'),
        t('Halmahera Selatan'),
        t('Halmahera Tengah'),
        t('Halmahera Timur'),
        t('Halmahera Utara'),
        t('Kepulauan Sula'),
        t('Pulau Morotai'),
        t('Ternate'),
        t('Tidore Kepulauan'),
      ));
      break;

    case 'Nanggroe Aceh Darussalam':
      return drupal_map_assoc(array(
        t('Aceh Barat'),
        t('Aceh Barat Daya'),
        t('Aceh Besar'),
        t('Aceh Jaya	236'),
        t('Aceh Selatan'),
        t('Aceh Singkil'),
        t('Aceh Tamiang'),
        t('Aceh Tengah'),
        t('Aceh Tenggara'),
        t('Aceh Timur'),
        t('Aceh Utara'),
        t('Banda Aceh'),
        t('Bener Meriah'),
        t('Bireuen'),
        t('Gayo Lues'),
        t('Langsa'),
        t('Lhokseumawe'),
        t('Nagan Raya'),
        t('Pidie'),
        t('Pidie Jaya'),
        t('Sabang'),
        t('Simeulue'),
        t('Subulussalam'),
      ));
      break;

    case 'Nusa Tenggara Barat':
      return drupal_map_assoc(array(
        t('Bima (Kab.)'),
        t('Bima (Kota)'),
        t('Dompu'),
        t('Lombok Barat'),
        t('Lombok Tengah'),
        t('Lombok Timur'),
        t('Lombok Utara'),
        t('Mataram'),
        t('Sumbawa'),
        t('Sumbawa Barat'),
      ));
      break;

    case 'Nusa Tenggara Timur':
      return drupal_map_assoc(array(
        t('Alor'),
        t('Belu'),
        t('Ende'),
        t('Flores Timur'),
        t('Kupang (Kab.)'),
        t('Kupang (Kota)'),
        t('Lembata'),
        t('Manggarai'),
        t('Manggarai Barat'),
        t('Manggarai Timur'),
        t('Nagekeo'),
        t('Ngada'),
        t('Rote Ndao'),
        t('Sabu Raijua'),
        t('Sikka'),
        t('Sumba Barat'),
        t('Sumba Barat Daya'),
        t('Sumba Tengah'),
        t('Sumba Timur'),
        t('Timor Tengah Selatan'),
        t('Timor Tengah Utara'),
      ));
      break;

    case 'Papua':
      return drupal_map_assoc(array(
        t('Asmat'),
        t('Biak Numfor'),
        t('Boven Digoel'),
        t('Deiyai (Deliyai)'),
        t('Dogiyai'),
        t('Intan Jaya'),
        t('Jayapura (Kab.)'),
        t('Jayapura (Kota)'),
        t('Jayawijaya'),
        t('Keerom'),
        t('Kepulauan Yapen (Yapen Waropen)'),
        t('Lanny Jaya'),
        t('Mamberamo Raya'),
        t('Mamberamo Tengah'),
        t('Mappi'),
        t('Merauke'),
        t('Mimika'),
        t('Nabire'),
        t('Nduga'),
        t('Paniai'),
        t('Pegunungan Bintang'),
        t('Puncak'),
        t('Puncak Jaya'),
        t('Sarmi'),
        t('Supiori'),
        t('Tolikara'),
        t('Waropen'),
        t('Yahukimo'),
        t('Yalimo'),
      ));
      break;

    case 'Papua Barat':
      return drupal_map_assoc(array(
        t('Fakfak'),
        t('Kaimana'),
        t('Manokwari'),
        t('Manokwari Selatan'),
        t('Maybrat'),
        t('Pegunungan Arfak'),
        t('Raja Ampat'),
        t('Sorong (Kab.)'),
        t('Sorong (Kota)'),
        t('Sorong Selatan'),
        t('Tambrauw'),
        t('Teluk Bintuni'),
        t('Teluk Wondama'),
      ));
      break;

    case 'Riau':
      return drupal_map_assoc(array(
        t('Bengkalis'),
        t('Dumai'),
        t('Indragiri Hilir'),
        t('Indragiri Hulu'),
        t('Kampar'),
        t('Kepulauan Meranti'),
        t('Kuantan Singingi'),
        t('Pekanbaru'),
        t('Pelalawan'),
        t('Rokan Hilir'),
        t('Rokan Hulu'),
        t('Siak'),
      ));
      break;

    case 'Sulawesi Barat':
      return drupal_map_assoc(array(
        t('Majene'),
        t('Mamasa'),
        t('Mamuju'),
        t('Mamuju Utara'),
        t('Polewali Mandar'),
      ));
      break;

    case 'Sulawesi Selatan':
      return drupal_map_assoc(array(
        t('Bantaeng'),
        t('Barru'),
        t('Bone'),
        t('Bulukumba'),
        t('Enrekang'),
        t('Gowa'),
        t('Jeneponto'),
        t('Luwu'),
        t('Luwu Timur'),
        t('Luwu Utara'),
        t('Makassar'),
        t('Maros'),
        t('Palopo'),
        t('Pangkajene Kepulauan'),
        t('Parepare'),
        t('Pinrang'),
        t('Selayar (Kepulauan Selayar)'),
        t('Sidenreng Rappang/Rapang'),
        t('Sinjai'),
        t('Soppeng'),
        t('Takalar'),
        t('Tana Toraja'),
        t('Toraja Utara'),
        t('Wajo'),
      ));
      break;

    case 'Sulawesi Tengah':
      return drupal_map_assoc(array(
        t('Banggai'),
        t('Banggai Kepulauan'),
        t('Buol'),
        t('Donggala'),
        t('Morowali'),
        t('Palu'),
        t('Parigi Moutong'),
        t('Poso'),
        t('Sigi'),
        t('Tojo Una-Una'),
        t('Toli-Toli'),
      ));
      break;

    case 'Sulawesi Tenggara':
      return drupal_map_assoc(array(
        t('Bau-Bau'),
        t('Bombana'),
        t('Buton'),
        t('Buton Utara'),
        t('Kendari'),
        t('Kolaka'),
        t('Kolaka Utara'),
        t('Konawe'),
        t('Konawe Selatan'),
        t('Konawe Utara'),
        t('Muna'),
        t('Wakatobi'),
      ));
      break;

    case 'Sulawesi Utara':
      return drupal_map_assoc(array(
        t('Bitung'),
        t('Bolaang Mongondow (Bolmong)'),
        t('Bolaang Mongondow Selatan'),
        t('Bolaang Mongondow Timur'),
        t('Bolaang Mongondow Utara'),
        t('Kepulauan Sangihe'),
        t('Kepulauan Siau Tagulandang Biaro (Sitaro)'),
        t('Kepulauan Talaud'),
        t('Kotamobagu'),
        t('Manado'),
        t('Minahasa'),
        t('Minahasa Selatan'),
        t('Minahasa Tenggara'),
        t('Minahasa Utara'),
        t('Tomohon'),
      ));
      break;

    case 'Sumatera Barat':
      return drupal_map_assoc(array(
        t('Agam'),
        t('Bukittinggi'),
        t('Dharmasraya'),
        t('Kepulauan Mentawai'),
        t('Lima Puluh Koto/Kota'),
        t('Padang'),
        t('Padang Panjang'),
        t('Padang Pariaman'),
        t('Pariaman'),
        t('Pasaman'),
        t('Pasaman Barat'),
        t('Payakumbuh'),
        t('Pesisir Selatan'),
        t('Sawah Lunto'),
        t('Sijunjung (Sawah Lunto Sijunjung)'),
        t('Solok (Kab.)'),
        t('Solok (Kota)'),
        t('Solok Selatan'),
        t('Tanah Datar'),
      ));
      break;

    case 'Sumatera Selatan':
      return drupal_map_assoc(array(
        t('Banyuasin'),
        t('Empat Lawang'),
        t('Lahat'),
        t('Lubuk Linggau'),
        t('Muara Enim'),
        t('Musi Banyuasin'),
        t('Musi Rawas'),
        t('Ogan Ilir'),
        t('Ogan Komering Ilir'),
        t('Ogan Komering Ulu'),
        t('Ogan Komering Ulu Selatan'),
        t('Ogan Komering Ulu Timur'),
        t('Pagar Alam'),
        t('Palembang'),
        t('Prabumulih'),
      ));
      break;

    case 'Sumatera Utara':
      return drupal_map_assoc(array(
        t('Asahan'),
        t('Batu Bara'),
        t('Binjai'),
        t('Dairi'),
        t('Deli Serdang'),
        t('Gunungsitoli'),
        t('Humbang Hasundutan'),
        t('Karo'),
        t('Labuhan Batu'),
        t('Labuhan Batu Selatan'),
        t('Labuhan Batu Utara'),
        t('Langkat'),
        t('Mandailing Natal'),
        t('Medan'),
        t('Nias'),
        t('Nias Barat'),
        t('Nias Selatan'),
        t('Nias Utara'),
        t('Padang Lawas'),
        t('Padang Lawas Utara'),
        t('Padang Sidempuan'),
        t('Pakpak Bharat'),
        t('Pematang Siantar'),
        t('Samosir'),
        t('Serdang Bedagai'),
        t('Sibolga'),
        t('Simalungun'),
        t('Tanjung Balai'),
        t('Tapanuli Selatan'),
        t('Tapanuli Tengah'),
        t('Tapanuli Utara'),
        t('Tebing Tinggi'),
        t('Toba Samosir'),
      ));
      break;

    case 'Yogyakarta DI':
      return drupal_map_assoc(array(
        t('Bantul'),
        t('Gunung Kidul'),
        t('Kulon Progo'),
        t('Sleman'),
        t('Yogyakarta'),
      ));
      break;

    default:
      return array(
        '' => t('--'),
      );
      break;
  }
}
