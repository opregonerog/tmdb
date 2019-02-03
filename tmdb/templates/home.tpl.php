 <?php global $user ?>
 <div id = "movies">
 <?php print l(t('Wishlist'),'wishlist');?>
   <?php print l(t('Movies'),'movie-list');?>
   <?php print l(t('Actors'),'actors-list');?>
 <?php $block = module_invoke('search', 'block_view', 'search'); ?>
 <div class = "row buscador">
     <?php print render($block); ?>
 </div>
 <div class = "recomended">
   <?php echo views_embed_view('movies_recomendations', 'block_1',$user->uid); ?>
 </div>
 <div class = "row upcoming-movies">
    <?php echo views_embed_view('movies', 'block'); ?>
 </div>
 <?php echo views_embed_view('actors', 'block'); ?>
 <?php echo views_embed_view('movies', 'block_1'); ?>
 </div>
 
 