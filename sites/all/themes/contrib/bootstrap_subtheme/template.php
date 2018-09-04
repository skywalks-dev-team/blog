<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

function bootstrap_subtheme_preprocess_page(&$variables) {
	global $user;
	if($user->uid == 1){
		$variables['margin_if_admin'] = '<style type="text/css">
		@media screen and (max-width: 980px){
			.main-container{margin-top: 25px;}header{top: 25px !important;}
		}
		@media screen and (max-width: 480px){
			.main-container{margin-top: 45px;}header{top: 45px !important;}
		}
		@media screen and (max-width: 360px){
			.main-container{margin-top: 72px;}header{top: 72px !important;}
		}
		</style>';
	}
	else{
		$variables['margin_if_admin'] = '';
	}
}
