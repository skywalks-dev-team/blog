<?php

/**
 * @file
 * The primary PHP file for this theme.
 */

function skywalks_preprocess_page(&$variables) {
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

function skywalks_theme() {
  $items = array();
	
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'skywalks') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'skywalks_preprocess_user_login'
    ),
  );
  return $items;
}
function skywalks_preprocess_user_login(&$vars) {
  $vars['intro_text'] = t('LOGIN');
}