// We define a function that takes one parameter named $.
(function ($) {
  // Use jQuery with the shortcut:
  // console.log($.browser);
  // Here we immediately call the function with jQuery as the parameter.
  jQuery(document).ready(function($) {
  	$('.no-letter').click(function(){
  		var test = $('.dash-menu').width();
  		if (test > 100) {
  			$('.dash-menu').css("width", "55px");
  			$(".level-1").children("a").css("color","transparent");
  			$(".level-1").children("a").css("overflow","hidden");
  			$(".svg-inline--fa").css("color","#fff");
  			// $('.level-1').children("a.dropdown-toggle").css("height", "10px");
  			$('.level-1').children("a.dropdown-toggle").css("width", "55px");
  			$('.level-1').children("a.dropdown-toggle").css("height", "55px");
  			$('.level-1').children("a").css("height", "45px");

  		}else{
  			$('.dash-menu').css("width", "");
  			$(".level-1").children("a").css("color","unset");
        $(".level-2").children("a").css("color","initial");
  			$('.level-1').children("a.dropdown-toggle").css("width", "initial");
  			$('.level-1').children("a.dropdown-toggle").css("height", "initial");
  			$('.level-1').children("a").css("height", "initial");
  		}
  	})
	});
}(jQuery));
