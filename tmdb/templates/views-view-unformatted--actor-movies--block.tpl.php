<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<h3><?php print t("Related Movies") ?></h3>
<section id = "bandaPrincipal">
  <div id="otrasPeliculas">
    <?php foreach ($rows as $id => $row): ?>
      <div class="peliculaSecundaria">
  	    <?php print $row; ?>
  	  </div>
    <?php endforeach; ?>
  </div>
</section>