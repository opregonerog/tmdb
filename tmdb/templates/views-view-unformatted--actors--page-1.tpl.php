<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<h3><?php print t("Actors") ?></h3>
<section id = "actoresDelMomento">
  <div id="contenedorActores">
    <?php foreach ($rows as $id => $row): ?>
      <div class="actorDestacado">
  	    <?php print $row; ?>
  	  </div>
    <?php endforeach; ?>
  </div>
</section>