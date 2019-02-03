<div>
	<?php foreach($movies as $movie):?>
		<div>
			<img src = "http://image.tmdb.org/t/p/w185//<?php print $movie->poster_path ?>">
			<a href="movie/<?php print $movie->id ?>"><?php print $movie->title ?></a>
		</div>
	<?php endforeach;?>
</div>