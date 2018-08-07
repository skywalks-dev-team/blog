<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

function bootstrap_subtheme_preprocess_page(&$variables) {
	global $user;
	if($user->uid == 1){
		$variables['margin_if_admin'] = "style='top: 30px;'";
	}
	else
  $variables['margin_if_admin'] = '';
}
