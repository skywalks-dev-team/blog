<?php
/**
 * @file
 * Entity form enhancements
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */


function intel_admin_entity_type_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'node_type_form') {
    $entity_type = 'node';
    $bundle = isset($form['#node_type']->type) ? $form['#node_type']->type : '';
  }
  elseif ($form_id == 'taxonomy_form_vocabulary') {
    $entity_type = 'taxonomy';
    $bundle = isset($form['#vocabulary']->machine_name) ? $form['#vocabulary']->machine_name : '';
  }
  else {
    return;
  }
  $form['intel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Intelligence'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',      
  ); 
  $form_state['intel'] = array(
    'entity_type' => $entity_type,
    'bundle' => $bundle,
  ); 
  $form['#submit'][] = 'intel_entity_type_form_submit';

  $entity_settings = array();
  // if new entity bundle, $bundle will not be set
  if ($bundle) {
    $entity_settings = variable_get('intel_entity_settings_' . $entity_type . '__' . $bundle, array());
  }
  $pi = intel_get_page_intents('select');
  $page_intents = array();
  foreach ($pi AS $key => $v) {
    $page_intents[$key] = $v['title'];
  }

  $form['intel']['intel_page_intent'] = array(
    '#type' => 'select',
    '#title' => t('Default page intent'),
    '#options' => $page_intents,
    '#default_value' => !empty($entity_settings['page_intent']) ? $entity_settings['page_intent'] : INTEL_PAGE_INTENT_DEFAULT,
    '#description' => t('Sets the default page intent for this content type. Defaults can be overriden per node using page_intent field.'),
  );

  if ($form_id == 'node_type_form') {
    $form['intel']['intel_track_page_uid'] = array(
      '#type' => 'checkbox',
      '#title' => t('Track author'),
      '#default_value' => !empty($entity_settings['track_page_uid']) ? $entity_settings['track_page_uid'] : 'a',
      '#description' => t('If enabled, node author will be tracked in analytics for this content type.'),
    );

    $options = array();
    $fields_info = field_info_instances($entity_type, $bundle);
    foreach ($fields_info AS $key => $field) {
      $field_info = field_info_field($key);
      if (isset($field_info['settings']['allowed_values'][0]['vocabulary'])) {
        $vocab_name = $field_info['settings']['allowed_values'][0]['vocabulary'];
        $options[$key] = $field['label'];
      }
    }
    $form['intel']['intel_track_term_fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Track vocabularies'),
      '#options' => $options,
      '#default_value' => !empty($entity_settings['track_term_fields']) ? $entity_settings['track_term_fields'] : array(),
      '#description' => t('If checked, any terms in the vocabulary will be added to page attributes.'),
    );
  }
  elseif ($form_id == 'taxonomy_form_vocabulary') {
    // alter page intent description
    $form['intel']['intel_page_intent']['#description'] = t('Set the page intent for this vocabulary\'s listing page.');

    // alter collapsed settings
    $form['intel']['#collapsed'] = (empty($entity_settings['track_page_terms']) && empty($entity_settings['page_attribute']['key']));

    $form['intel']['intel_track_page_terms'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add selected terms to page attributes on all content types.'),
      '#default_value' => !empty($entity_settings['track_page_terms']) ? $entity_settings['track_page_terms'] : INTEL_TRACK_PAGE_TERMS_DEFAULT,
      '#description' => t('Check to enable term in this vocabulary to be automatically tracked in analytics on all content types. In left unchecked, you can configure tracking settings on per content type via the content type edit form.'),
    );

    $form['intel']['intel_sync_visitor_terms'] = array(
      '#type' => 'checkbox',
      '#title' => t('Sync term attributes in api visitor data with Drupal visitor entity.'),
      '#default_value' => !empty($entity_settings['sync_visitor_terms']) ? $entity_settings['sync_visitor_terms'] : INTEL_SYNC_VISITOR_TERMS_DEFAULT,
      '#description' => t('If enabled, any terms associated with the Visitor entity in Drupal will be synced with the api data. Terms can be set using custom fields.'),
    );

    $form['intel']['page_attribute'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom page/visitor attribute'),
      '#description' => t('By default vocabularies are tracked as standard Taxomony terms. Use the below fields create a custom page attribute to track this vocabulary.'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($entity_settings['page_attribute']['key']),
    );

    $form['intel']['page_attribute']['intel_page_attribute_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Key'),
      '#default_value' => !empty($entity_settings['page_attribute']['key']) ? $entity_settings['page_attribute']['key'] : '',
      '#description' => t('A short unique identifier for the attribute. Keep this a short as possible.'),
      '#size' => 12,
    );

    $form['intel']['page_attribute']['intel_page_attribute_prop'] = array(
      '#type' => 'textfield',
      '#title' => t('Property'),
      '#default_value' => !empty($entity_settings['page_attribute']['prop']) ? $entity_settings['page_attribute']['prop'] : '',
      '#description' => t('Identifier for this attribute.'),
      '#size' => 32,
    );

    $form['intel']['page_attribute']['intel_page_attribute_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title override'),
      '#default_value' => !empty($entity_settings['page_attribute']['title']) ? $entity_settings['page_attribute']['title'] : '',
      '#description' => t('Human friendly attribute title to displayed to site administrators. Leave blank to use vocabulary\'s name.'),
      '#size' => 32,
    );

    $form['intel']['page_attribute']['intel_page_attribute_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description override'),
      '#default_value' => !empty($entity_settings['page_attribute']['description']) ? $entity_settings['page_attribute']['description'] : '',
      '#description' => t('Description of the attribute. Leave blank to use vocabulary\'s description.'),
      '#rows' => 2,
    );



    /*
    $form['intel']['intel_track_page_terms_visitor'] = array(
      '#type' => 'checkbox',
      '#title' => t('Track selected terms in visitor attributes on all content types.'),
      '#default_value' => !empty($entity_settings['track_page_terms_visitor']) ? $entity_settings['track_page_terms_visitor'] : INTEL_TRACK_PAGE_TERMS_VISITOR_DEFAULT,
      '#description' => t('Check to enable term in this vocabulary to be automatically tracked in analytics on all content types. In left unchecked, you can configure tracking settings on per content type via the content type edit form.'),
    );

    $form['intel']['visitor_attribute'] = array(
      '#type' => 'fieldset',
      '#title' => t('Custom visitor attribute'),
      '#description' => t('By default vocabularies the settings for the page attributes will be used to track in visitor attributes. Use the field below, if you would like to track this vocabulary\'s terms as a different visitor attribute.'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($entity_settings['visitor_attribute']['key']),
    );
    $form['intel']['visitor_attribute']['intel_visitor_attribute_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Key'),
      '#default_value' => !empty($entity_settings['visitor_attribute']['key']) ? $entity_settings['visitor_attribute']['key'] : '',
      '#description' => t('A short unique identifier for the attribute. Keep this a short as possible.'),
      '#size' => 12,
    );

    $form['intel']['visitor_attribute']['intel_visitor_attribute_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title override'),
      '#default_value' => !empty($entity_settings['visitor_attribute']['title']) ? $entity_settings['visitor_attribute']['title'] : '',
      '#description' => t('Human friendly attribute title to displayed to site administrators. Leave blank to use vocabulary\'s name.'),
      '#size' => 32,
    );

    $form['intel']['visitor_attribute']['intel_visitor_attribute_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description override'),
      '#default_value' => !empty($entity_settings['visitor_attribute']['description']) ? $entity_settings['visitor_attribute']['description'] : '',
      '#description' => t('Description of the attribute. Leave blank to use vocabulary\'s description.'),
      '#rows' => 2,
    );
    */

    $form['intel']['cms'] = array(
      '#type' => 'fieldset',
      '#title' => t('CMS integration'),
      //'#description' => t(''),
      '#collapsible' => TRUE,
      '#collapsed' => empty($entity_settings['cms']['key']),
    );

    $empty = 1;
    if (module_exists('intel_mailchimp')) {
      $form['intel']['cms']['intel_cms_mailchimp_group_field'] = array(
        '#type' => 'textfield',
        '#title' => t('MailChimp Group Field'),
        '#default_value' => !empty($entity_settings['cms']['mailchimp_group_field']) ? $entity_settings['cms']['mailchimp_group_field'] : '',
        '#description' => t('Enter the the name of the MailChimp Group'),
      );
      $empty = 0;
    }

    if ($empty) {
      $form['intel']['cms']['empty'] = array(
        '#type' => 'markup',
        '#markup' => t('No CMS integration modules have been enabled.'),
      );
    }
  }
}
// TODO: should this be converted to use a entity_type_insert hook?
function intel_admin_entity_type_form_submit($form, &$form_state) {
  if (!isset($form_state['intel'])) {
    return;
  }

  $values = $form_state['values'];
  $entity_type = $form_state['intel']['entity_type'];
  $bundle = $form_state['intel']['bundle'];
  if (!$bundle && !empty($values['machine_name'])) {
    $bundle = $values['machine_name'];
  }

  $entity_settings = array();

  if (isset($values['intel_page_intent'])) {
    $entity_settings['page_intent'] = $values['intel_page_intent'];
  }

  if (isset($values['intel_track_page_uid'])) {
    $entity_settings['track_page_uid'] = $values['intel_track_page_uid'];
  }
  if (isset($values['intel_track_term_fields'])) {
    $entity_settings['track_term_fields'] = $values['intel_track_term_fields'];
  }

  if (isset($values['intel_track_page_terms'])) {
    $entity_settings['track_page_terms'] = $values['intel_track_page_terms'];
  }

  if (!empty($values['intel_page_attribute_key'])) {
    if (!isset($entity_settings['page_attribute'])) {
      $entity_settings['page_attribute'] = array();
    }
    $entity_settings['page_attribute']['key'] = $values['intel_page_attribute_key'];
    if (!empty($values['intel_page_attribute_prop'])) {
      $entity_settings['page_attribute']['prop'] = $values['intel_page_attribute_prop'];
    }
    if (!empty($values['intel_page_attribute_title'])) {
      $entity_settings['page_attribute']['title'] = $values['intel_page_attribute_title'];
    }
    if (!empty($values['intel_page_attribute_description'])) {
      $entity_settings['page_attribute']['description'] = $values['intel_page_attribute_description'];
    }
  }

  if (isset($values['intel_sync_visitor_terms'])) {
    $entity_settings['sync_visitor_terms'] = $values['intel_sync_visitor_terms'];
    $entity_settings['visitor_attribute'] = array();
    $entity_settings['visitor_attribute']['key'] = $values['intel_page_attribute_key'];
    if (!empty($values['intel_page_attribute_prop'])) {
      $entity_settings['visitor_attribute']['prop'] = $values['intel_page_attribute_prop'];
    }
  }

  /*
  if (isset($values['intel_track_page_terms_visitor'])) {
    $entity_settings['track_page_terms_visitor'] = $values['intel_track_page_terms_visitor'];
  }
  if (!empty($values['intel_visitor_attribute_key'])
    || !empty($values['intel_visitor_attribute_title'])
    || !empty($values['intel_visitor_attribute_description'])
  ) {
    if (!isset($entity_settings['visitor_attribute'])) {
      $entity_settings['visitor_attribute'] = array();
    }
    $entity_settings['visitor_attribute']['key'] = $values['intel_visitor_attribute_key'];
    if (!empty($values['intel_visitor_attribute_title'])) {
      $entity_settings['visitor_attribute']['title'] = $values['intel_visitor_attribute_title'];
    }
    if (!empty($values['intel_visitor_attribute_description'])) {
      $entity_settings['visitor_attribute']['description'] = $values['intel_visitor_attribute_description'];
    }
  }
  */

  if (!empty($values['intel_cms_mailchimp_group_field'])) {
    $entity_settings['cms']['mailchimp_group_field'] = $values['intel_cms_mailchimp_group_field'];
  }

  variable_set('intel_entity_settings_' . $entity_type . '__' . $bundle, $entity_settings);
}



function intel_admin_entity_edit_form_alter(&$form, &$form_state, $form_id = '') {
  drupal_add_css(drupal_get_path('module', 'intel') . "/css/intel.entity_edit.css");
  drupal_add_js(drupal_get_path('module', 'intel') . "/js/intel.entity_edit.js");
  
  $form_add = array(
    '#type' => 'fieldset',
    '#title' => t('Intelligence'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',  
    '#attributes' => array(
      'class' => array('intel-vert-tab'),
    ),  
  ); 
  $field_count = 0;
  $lang = !empty($form['language']['#value']) ? $form['language']['#value'] : LANGUAGE_NONE;
	if ((!empty($form['field_page_attribute_col']['#access']) && $form['field_page_attribute_col']['#access'] == TRUE) ||
		(!empty($form['field_visitor_attribute_col']['#access']) && $form['field_visitor_attribute_col']['#access'] == TRUE) ||
		(!empty($form['field_intel_event_col']['#access']) && $form['field_intel_event_col']['#access'] == TRUE)) {
		if (isset($form['field_page_intent'])) {
			$form_add['field_page_intent'] = $form['field_page_intent'];
			unset($form['field_page_intent']);
			$field_count++;
		}
		if (isset($form['field_page_attribute_col'])) {
			$form_add['field_page_attribute_col'] = $form['field_page_attribute_col'];
			unset($form['field_page_attribute_col']);
			$field_count++;
		}
		if (isset($form['field_visitor_attribute_col'])) {
			$form_add['field_visitor_attribute_col'] = $form['field_visitor_attribute_col'];
			unset($form['field_visitor_attribute_col']);
			$field_count++;
		}
		if (isset($form['field_intel_event_col'])) {
			$form_add['field_intel_event_col'] = $form['field_intel_event_col'];
			unset($form['field_intel_event_col']);
			$field_count++;
		}

    if (!empty($form['#entity']) && !empty($form['#entity_type'])) {
      $api_level = intel_api_level();
      $emsgs = array(
        'page' => t('Page attribute features are not available with the free version of Intelligence.'),
        'visitor'  => t('Visitor attribute features are not available with the free or basic versions of Intelligence.'),
      );
      $attrs = intel_get_entity_intel_attributes($form['#entity'], $form['#entity_type'], 1);
      $scopes = array('page', 'visitor');
      for ($i = 0; $i < count($scopes); $i++) {
        $scope = $scopes[$i];

        if (!empty($attrs[$scope])) {
          $attr_info = intel_get_attribute_info(NULL, $scope);
          $items = array();

          foreach ($attrs[$scope] as $k => $v) {
            $msg = '';
            if ($api_level != 'pro') {
              if ($scope == 'page' && $api_level != 'basic') {
                $msg = "<div class=\"messages warning\">\n" . $emsgs['page'] . "\n</div>";
              }
              else if ($scope == 'visitor') {
                $msg = "<div class=\"messages warning\">\n" . $emsgs['visitor'] . "\n</div>";
              }
            }
            $item = $attr_info[$k]['title'] . ' (' . $k . ')'; // . ' (' . $attr_info[$k]['type'] . ')';
            if ($attr_info[$k]['type'] == 'value' || $attr_info[$k]['type'] == 'scalar') {
              $item .= ': ' . $v;
            }
            else if ($attr_info[$k]['type'] == 'item') {
              $option = intel_get_attribute_option_info($scope, $k, $v);
              $item .= ': ' . $option['title']. ' (' . $v . ')';
            }
            else if ($attr_info[$k]['type'] == 'list' || $attr_info[$k]['type'] == 'vector') {
              if (is_array($v)) {
                $items2 = array();
                foreach ($v as $kk => $vv) {
                  $option = intel_get_attribute_option_info($scope, $k, $kk);
                  $item2 = '';
                  if (!empty($option['title'])) {
                    $item2 .= '' . $option['title']. ' (' . $kk . ')';
                  }
                  if (!empty($vv)) {
                    $item2 .= ': ' . $vv;
                  }
                  $items2[] = $item2;

                }
                $item .= ':' . theme('item_list', array('items' => $items2));
              }
            }
            $items[] = $item;
          }
          $vars = array(
            'title' => ($scope == 'page') ? t('Page attributes') : t('Visitor attributes'),
            'items' => $items,
            'type' => 'ul',
          );
          $form_add['intel_' . $scope . '_attrs_active'] = array(
            '#type' => 'markup',
            '#markup' => $msg . theme('item_list', $vars),
          );
          $field_count++;
        }

      }
    }

		if ($field_count) {
			$form['intel'] = $form_add;
		}

		if (isset($form['field_visitor_category_col'])) {
			$form['field_visitor_category_col']['#prefix'] = '<div class="intel-visitor-action-col">';
			$form['field_visitor_category_col']['#suffix'] = '</div>';
		}
  }
  //dsm($form);
  
}
