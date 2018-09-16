// We define a function that takes one parameter named $.
(function ($) {
  // Use jQuery with the shortcut:
  // console.log($.browser);
  // Here we immediately call the function with jQuery as the parameter.
  jQuery(document).ready(function($) {
  	$('.no-letter').click(function(){
      var element = document.getElementById('dash-menu');
  		var test = $('.dash-menu').width();
  		if (test > 100) {
        $('#dash-menu').removeClass('col-md-3');
  			$('.dash-menu').css("width", "55px");
        $("li.tb-megamenu-item.level-2.mega").children("a").css("color","transparent");
  			$("li.tb-megamenu-item.level-2.mega").children("i").css("color","#fff");
        $(".level-1").children("a").css("overflow","hidden");
  			$(".svg-inline--fa").css("color","#fff");
  			// $('.level-1').children("a.dropdown-toggle").css("height", "10px");
  			$('.level-1').children("a.dropdown-toggle").css("width", "55px");
  			$('.level-1').children("a.dropdown-toggle").css("height", "55px");
  			$('.level-1').children("a").css("height", "45px");
        $('.level-1').children("a").css("width", "55px");
        $('.tb-megamenu-nav.nav.level-0.items-6').css("width", "55px");
        $('.region.region-sidebar-first').css("width", "55px");

  		}else{
        $('.dash-menu').css("width", "initial");
        $("li.tb-megamenu-item.level-1.mega.tb-3.mega-align-left.dropdown").children("a").css("color","#fff");
        $("li.tb-megamenu-item.level-2.mega").children("a").css("color","#fff");
        $('.level-1').children("a.dropdown-toggle").css("width", "270px");
        $('.level-1').children("a.dropdown-toggle").css("height", "65px");
        $('.level-1').children("a").css("height", "55px");
        $('.level-1').children("a").css("width", "270px");
        $('.tb-megamenu-nav.nav.level-0.items-6').css("width", "270px");
        $('.region.region-sidebar-first').css("width", "270px");
        $('#dash-menu').addClass('col-md-3');
      }
  	})
	});
}(jQuery));
