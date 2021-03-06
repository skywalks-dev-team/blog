<?php

function intel_webform_admin_submission_results_alter_js() {
  // strip starting /
  $a = explode("/", $_POST['path']);  
  $wf_path = 'node/' . $a[2] . "/submission/"; 
  //require_once './' . drupal_get_path('module', 'l10insight') . "/l10insight.report.inc";
  $steps = array();
  $request = array(
    'dimensions' => array('ga:dimension5', 'ga:visitCount', 'ga:date', 'ga:city', 'ga:region', 'ga:country', 'ga:eventLabel'),
    //'dimensions' => array('ga:pagePath'),
    'metrics' => array('ga:uniqueEvents'),
    'sort_metric' => '-ga:date',
    'start_date' => strtotime("-365 days"),
    'end_date' => strtotime("Today"),
    'max_results' => 1000,
    'filters' => "ga:eventLabel=~^{$wf_path}*",
    //'segment' => 'dynamic::ga:customVarValue5==1337759660',
  );
  $data = intel_ga_api_data($request);

  $rows = array();
  if (!empty($data->results) && is_array($data->results)) {
    foreach ($data->results AS $r) {
      $a = explode("/", $r['eventLabel']);
      $sid = $a[3];
      if (!empty($_POST['sids'][$sid])) {
        $rows[$sid] = '<td>' . "{$r['city']}, {$r['region']}, {$r['country']}" . '</td><td>' . l(t('Intel'), 'visitor/' . $r['dimension5']) . '</td>';
      }
    }
  }
  $output['rows'] = $rows;
  $output['rowcount'] = count($rows);
//return '';
  drupal_json_output($output);
}