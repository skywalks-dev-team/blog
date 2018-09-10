<?php
function skyblog_preprocess_page(&$variables) {
	global $user;
	global $base_url;
	// drupal_add_css(drupal_get_path('theme', 'skyblog') . '/css/not-admin.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	if (($user->uid != 1) && ($user->uid != 5)) {
		$css = drupal_get_path('module', 'sky_dashboard')."/css/not-admin.css";
		drupal_add_css($css,array('group' => CSS_DEFAULT, 'every_page' => TRUE));
		pr(drupal_add_css($css,array('group' => CSS_DEFAULT, 'every_page' => TRUE)));
	}
	else{
		pr('test2');
		return true;
		
	}
}
