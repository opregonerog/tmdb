<?php
  
function tmdb_form($form, &$form_state) {

  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );
  $form['tmdb_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuración General'),
    '#collapsible' => true,
    '#collapsed' => false,
    '#group' => 'settings',
  );
  $form['tmdb_settings']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('api_key'),
    '#default_value' => variable_get('api_key', ''),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
    '#description' => 'Write api_key',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function tmdb_form_submit($form, &$form_state){
  variable_set('aṕi_key',$form_state['values']['api_key']);
  import_data();
}

function create_genres(){
  $url = "https://api.themoviedb.org/3/genre/movie/list";
  $genres = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  $genres_list =json_decode($genres);
  $vocabulary = taxonomy_vocabulary_machine_name_load("genre");
  $vid = $vocabulary->vid;
  foreach($genres_list->genres as $genre){
    taxonomy_term_save((object) array(
      'name' => $genre->name,
      'vid' => $vid,
      'weight' => 0,
    ));
  }
}

function get_cast($id){
  $url = "https://api.themoviedb.org/3/movie/".$id."/credits";  
  $cast = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  return json_decode($cast);
}

function get_alternative_titles($id)  {
  $url = "https://api.themoviedb.org/3/movie/".$id."/alternative_titles";  
  $alternative_titles = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  return json_decode($alternative_titles);
}

function get_trailler($id)  {
  $url = "https://api.themoviedb.org/3/movie/".$id."/videos";  
  $videos = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  return json_decode($videos);
}

function create_actor($id){
  global $user;
  $url = "https://api.themoviedb.org/3/person/".$id;
  $actor = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  $info = json_decode($actor,true);
  $node = new stdClass();
  $node->title = $info['name'];
  $node->type = 'actor';  
  $node->language = LANGUAGE_NONE; 
  $node->uid = $user->uid; 
  $node->status = 1; 
  $node->promote = 0; 
  $node->actor_photo['und'][0]['value'] = $info["profile_path"];
  $node->actor_popularity['und'][0]['value'] = $info["popularity"];
  $node->actor_bio['und'][0]['value'] = $info["biography"];
  $node->actor_name['und'][0]['value'] = $info["name"];
  $node->actor_birthdate['und'][0]['value'] = $info["birthday"];
  $node->actor_birth_place['und'][0]['value'] = $info["place_of_birth"];
  $node->actor_deathdate['und'][0]['value'] = $info["deathday"];
  $node->actor_website['und'][0]['value'] = $info["homepage"];  
  node_save($node);
  return ($node);
}

function create_movie($id) {
  global $user;    
  $actors = array();
  $cast = get_cast($id);
  foreach ($cast->cast as $person) {
    $actors[] = create_actor($person->id)->nid;
  }
  $url = "https://api.themoviedb.org/3/movie/".$id;
  $movie = drupal_http_request($url."?api_key=".variable_get('api_key',''))->data;
  $info = json_decode($movie,true);  
  $node = new stdClass();
  $node->title = $info['original_title'];
  $node->type = 'movie';  
  $node->language = LANGUAGE_NONE; 
  $node->uid = $user->uid; 
  $node->status = 1; 
  $node->promote = 0;   
  $node->movie_photo['und'][0]['value'] = $info["poster_path"]; 
  $node->movie_overview['und'][0]['value'] = $info["overview"];
  $node->movie_release_date['und'][0]['value'] = $info["release_date"];
  $node->movie_original_language['und'][0]['value'] = $info["original_language"];
  $node->movie_popularity['und'][0]['value'] = $info["popularity"];
  $videos = $trailler = get_trailler($id)->results;
  $node->movie_trailer['und'][0]['value'] = $videos[0]->key;
  $alternative_titles_string = "";
  $alternative_titles = get_alternative_titles($id)->titles;
  foreach ($alternative_titles as $alternative_title) {
    $alternative_titles_string.=$alternative_title->title." ";
  } 
  $node->movie_alternative_titles['und'][0]['value'] = $alternative_titles_string;
  $productions = "";
  foreach($info['production_companies'] as $companie) {
    $productions.=$companie['name'].",";
  }
  $node->movie_production_companies['und'][0]['value'] = $productions;
  $actors_counter = 0;
  foreach($actors as $actor){
    $node->movie_cast['und'][$actors_counter]['target_id'] = $actor;
    $actors_counter++;
  }
  $genres_counter = 0; 
  foreach($info['genres'] as $genre){  
    $node->movie_genres['und'][$genres_counter]['tid'] = array_shift(taxonomy_get_term_by_name($genre['name']))->tid;
    $genres_counter++;
  }
  node_save($node);  
}

function import_data(){
  global $user;
  //create_genres();      
  $url = "https://api.themoviedb.org/3/discover/movie/";
  $movies_data = drupal_http_request($url."?api_key=".variable_get('api_key','')."&page=4")->data;  
  $movies =json_decode($movies_data)->results; 
  foreach ($movies as $movie) {    
     create_movie($movie->id);  
  }
}


