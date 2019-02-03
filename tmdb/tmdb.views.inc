<?php 

function tmdb_views_data() {
  $data['wish_list']['table']['group'] = t('Wishlist');

  $data['wish_list']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('User wishlist'),
  );

  $data['wish_list']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  
  $data['wish_list']['nid'] = array(
    'title' => t('node nid'),
    'relationship'=> array(
      'base' => 'node',
      'base_field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('nid'),
    ),
  );

  $data['wish_list']['uid'] = array(
    'title' => t('user uid'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship'=> array(
      'base' => 'users',
      'base_field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('uid'),
    ),
  );

  $data['movies_recomendations']['table']['group'] = t('Movies Recomendatios');

  $data['movies_recomendations']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Movies Recomendatios'),
  );

  $data['movies_recomendations']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  
  $data['movies_recomendations']['nid'] = array(
    'title' => t('node nid'),
    'relationship'=> array(
      'base' => 'node',
      'base_field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('nid'),
    ),
  );
  $data['movies_recomendations']['uid'] = array(
    'title' => t('user uid'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship'=> array(
      'base' => 'users',
      'base_field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('uid'),
    ),
  );
  
  return $data;
}