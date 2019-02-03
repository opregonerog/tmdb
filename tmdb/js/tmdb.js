(function ($) {
  $(document).ready(function(){
  	jQuery('.rel-movie').click(function(e){
	  e.preventDefault();
	  jQuery.ajax({
  	    type: "POST",
        url: 'ajax/add_movie',
        data: { nid: jQuery(this).attr('href')},
        dataType: "json"
      });
	})    
  });
})(jQuery);