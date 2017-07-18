<?
error_reporting(E_ALL);
//ini_set("display_errors", 1);

require_once("../config.inc");
session_register("userid");
session_register("username");
session_register("userdisplayname");
session_register("administrator");
session_register("editor");
session_register("contributor");

if (strlen($_SESSION['username'])<1) {
	header("Location: ../login/index2.php");
}

require_once($_CFG['rootDirAdmin'].'functions/data_connect.inc');
require_once($_CFG['functionWebAdmin'].'functions2.inc');

if ($viewcookie = getCookie('view')) {
	$view = $viewcookie['view'];
} else {
	die('View not set.');
	//$view = "active";
}
$parameters = getCookie($view.'_search_parameters');
//echo "<pre>";
//print_r($parameters);
//echo "</pre>";
//die();
if (!($parameters = getCookie($view.'_search_parameters'))) {
	die('Search parameters not set.');
}
/*
// Removed because we want the advanced search to change back to the original selection before file.
if ($parameters['search_results_as'] != 'file') {
	die('Invalid option.');
	exit;
}
*/
// Advanced search
$advanced_search = 1;
include ('issues_query.inc');		// creates the query and returns $result

$author_names = array();
$cat_display = array();

function cleanData($str) {
	return $str;
	$str = preg_replace("/\t/", "\\t", $str);
	$str = preg_replace("/\r?\n/", "\\n", $str);
	if(strstr($str, '"'))	$str = '"' . str_replace('"', '""', $str) . '"';
	return $str;
}

// Copy and edit this switch struct from issues.php
switch ($view) {
	case 'publications': 
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Title', 'type' => 'text', 'output' => 'issue_title'),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'type' => 'hidden', 'output' => 'created_date'),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'type' => 'hidden', 'output' => 'modified_date'),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'type' => 'textarea', 'output' => 'issue_description'),
			'publication'			=> array('id' => 'publication', 'label' => 'Publication Type', 'type' => 'select', 'output' => 'publication_type'),
			'author'					=> array('id' => 'author', 'label' => 'Author', 'type' => 'select', 'output' => 'author'),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'type' => 'multiple', 'output' => 'output_users'),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'type' => 'select', 'output' => 'unit'),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'type' => 'select', 'output' => 'center'),
			'activity'				=> array('id' => 'activity', 'label' => 'Activity', 'type' => 'select', 'output' => 'activity'),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'type' => 'multiple', 'output' => 'output_topics'),
			'priority'				=> array('id' => 'priority', 'label' => 'Priority', 'type' => 'select', 'output' => 'priority'),
			'status'					=> array('id' => 'status', 'label' => 'Status', 'type' => 'select', 'output' => 'status'),
			'assigned_date'		=> array('id' => 'assigned_date', 'label' => 'Assigned Date', 'type' => 'date', 'output' => 'assigned_date'),
			'due_date'				=> array('id' => 'due_date', 'label' => 'Due Date', 'type' => 'date', 'output' => 'due_date'),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Completed Date', 'type' => 'date', 'output' => 'completed_date'),
			'on_time'					=> array('id' => 'on_time', 'label' => 'On Time', 'type' => 'select', 'output' => 'on_time'),
			'grant'						=> array('id' => 'grant', 'label' => 'Grant', 'type' => 'select', 'output' => 'grant_name'),
			'approved'				=> array('id' => 'approved', 'label' => 'Concept/Outline Approved', 'type' => 'select', 'output' => 'approved'),
			'hours'						=> array('id' => 'hours', 'label' => 'Hours', 'type' => 'text', 'output' => 'issue_hours'),
			);
		break;
	case 'contacts': 
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Contact', 'type' => 'text', 'output' => 'issue_title'),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'type' => 'hidden', 'output' => 'created_date'),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'type' => 'hidden', 'output' => 'modified_date'),
			'contact_office'	=> array('id' => 'contact_office', 'label' => 'Office', 'type' => 'select', 'output' => 'contact_office'),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'type' => 'multiple', 'output' => 'output_users'),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'type' => 'select', 'output' => 'unit'),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'type' => 'select', 'output' => 'center'),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'type' => 'multiple', 'output' => 'output_topics'),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Date', 'type' => 'date', 'output' => 'completed_date'),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'type' => 'textarea', 'output' => 'issue_description'),
			);
		break;
	default: 
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Title', 'type' => 'text', 'output' => 'issue_title'),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'type' => 'hidden', 'output' => 'created_date'),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'type' => 'hidden', 'output' => 'modified_date'),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'type' => 'textarea', 'output' => 'issue_description'),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'type' => 'multiple', 'output' => 'output_users'),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'type' => 'select', 'output' => 'unit'),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'type' => 'select', 'output' => 'center'),
			'type'						=> array('id' => 'type', 'label' => 'Type', 'type' => 'select', 'output' => 'type'),
			'activity'				=> array('id' => 'activity', 'label' => 'Activity', 'type' => 'select', 'output' => 'activity'),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'type' => 'multiple', 'output' => 'output_topics'),
			'priority'				=> array('id' => 'priority', 'label' => 'Priority', 'type' => 'select', 'output' => 'priority'),
			'status'					=> array('id' => 'status', 'label' => 'Status', 'type' => 'select', 'output' => 'status'),
			'assigned_date'		=> array('id' => 'assigned_date', 'label' => 'Assigned Date', 'type' => 'date', 'output' => 'assigned_date'),
			'due_date'				=> array('id' => 'due_date', 'label' => 'Due Date', 'type' => 'date', 'output' => 'due_date'),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Completed Date', 'type' => 'date', 'output' => 'completed_date'),
			'on_time'					=> array('id' => 'on_time', 'label' => 'On Time', 'type' => 'select', 'output' => 'on_time'),
			'grant'						=> array('id' => 'grant', 'label' => 'Grant', 'type' => 'select', 'output' => 'grant_name'),
			'approved'				=> array('id' => 'approved', 'label' => 'Concept/Outline Approved', 'type' => 'select', 'output' => 'approved'),
			'hours'						=> array('id' => 'hours', 'label' => 'Hours', 'type' => 'text', 'output' => 'issue_hours'),
			);
		break;
}

$tab_output = "";
$csv_output = "";
foreach ($viewform as $key => $array) {
	if ($array['type'] != "hidden") {
		$tab_output .= $array['label']." \t";
		if ($csv_output != "") $csv_output .= ",";
		//$csv_output .= $array['label'];
		$csv_output .= '"'.$array['label'].'"';
	}
}
$tab_output .= 'Notes \t';
$csv_output .= ',"Notes"';
//$csv_output .= ',Notes';
$tab_output .= " \n";
$csv_output .= "\n";

$file_output = $csv_output;
$debug_output = $csv_output."<br />";

while ($task = mysql_fetch_array($result)) {

	$tab_output = "";
	$csv_output = "";

	// get the notes
	$query2 = "SELECT * FROM track_notes WHERE issue_id='".$task['issue_id']."' ORDER BY note_date ASC";
	$result2 = mysql_query($query2) or die('Error, query failed - '.mysql_error());
	$output_notes = "";
	while ($note = mysql_fetch_array($result2)) {
		if ($output_notes != "") $output_notes .= "; ";
		$output_notes .= $note['note_date'];

		if (!isset($author_names[($note['note_created_by'])])) {
			$query3 = "SELECT user_id,user_name FROM track_users WHERE user_id='".$note['note_created_by']."' LIMIT 1";
			$result3 = mysql_query($query3);
			if ($author = mysql_fetch_array($result3)) {
				$author_names[($author['user_id'])] = $author['user_name'];
			}
		}
		$output_notes .= " by ".$author_names[($author['user_id'])];
		
		$output_notes .= ": ";
		$output_notes .= $note['note_note'];
	}

	// load staff (multiple selections)
	$output_users = "";
	$first = true;
	$id_set = explode(',',$task['issue_assigned_staff_ids']);
	foreach ($id_set as $value) {
		if ($first) {
			$first = false;
		} else {
			$output_users .= "; ";
		}
		if (!isset($user_display[$value])) {
			$query4 = "SELECT user_id,user_name FROM track_users WHERE user_id='".$value."' LIMIT 1";
			$result4 = mysql_query($query4);
			if ($user = mysql_fetch_array($result4)) {
				$user_display[$value] = $user['user_name'];
			}
		}
		$output_users .= $user_display[$value];
	}

	// load topics (multiple selections)
	$output_topics = "";
	$first = true;
	$id_set = explode(',',$task['issue_topic_ids']);
	foreach ($id_set as $value) {
		if ($first) {
			$first = false;
		} else {
			$output_topics .= "; ";
		}
		if (!isset($cat_display[$value])) {
			$query4 = "SELECT cat_id,cat_title FROM track_categories WHERE cat_id='".$value."' LIMIT 1";
			$result4 = mysql_query($query4);
			if ($cat = mysql_fetch_array($result4)) {
				$cat_display[$value] = $cat['cat_title'];
			}
		}
		$output_topics .= $cat_display[$value];
	}

	$first = true;
	// get each field according to task type in $viewform
	foreach ($viewform as $key => $array) {
		if ($array['type'] != "hidden") {
//echo "<pre>";
//print_r($array);
//echo "</pre>";
			if ($array['type'] == "multiple") {
//		echo $array['output'].": ";
//		echo ${$array['output']}."<br>";
				$tab_output .= ${$array['output']}."\t";
				if ($first) {
					$first = false;
				} else {
					$csv_output .= ",";
				}
				//$csv_output .= str_replace(",","¸",${$array['output']});
				//$csv_output .= '"'.str_replace('"','\"',${$array['output']}).'"';
				$csv_output .= '"'.str_replace('"',"'",${$array['output']}).'"';

			} elseif ($array['type'] == "select" || $array['type'] == "date") {
				$tab_output .= $task[$array['output']]."\t";
				if ($first) {
					$first = false;
				} else {
					$csv_output .= ",";
				}
				//$csv_output .= str_replace(",","¸",$task[$array['output']]);
				//$csv_output .= '"'.str_replace('"','\"',$task[$array['output']]).'"';
				$csv_output .= '"'.str_replace('"',"'",$task[$array['output']]).'"';
			} elseif ($array['type'] == "text" || $array['type'] == "textarea")  {
//			} else {
				$tab_output .= cleanData($task[$array['output']])."\t";
				if ($first) {
					$first = false;
				} else {
					$csv_output .= ",";
				}
				//$csv_output .= str_replace(",","¸",cleanData($task[$array['output']]));
				//$csv_output .= '"'.str_replace('"','\"',cleanData($task[$array['output']])).'"';
				$csv_output .= '"'.str_replace('"',"'",cleanData($task[$array['output']])).'"';
			} else {
				$tab_output .= "(unknown type for $key)\t";
				if ($first) {
					$first = false;
				} else {
					$csv_output .= ",";
				}
				$csv_output .= "(unknown type for $key)";
			}

		}
	}

	$tab_output .= $output_notes."\t";
	$tab_output .= "\n";

	//$csv_output .= ','.str_replace(",","¸",cleanData($output_notes));
	//$csv_output .= ','.'"'.str_replace('"','\"',cleanData($output_notes)).'"';
	$csv_output .= ','.'"'.str_replace('"',"'",cleanData($output_notes)).'"';
	$csv_output .= "\n";
	
	$file_output .= $csv_output;
	$debug_output .= $csv_output."<br />";
}
//echo $debug_output;
//die();
//$filename = "track_export_".date("Y-m-d").".tsv";
$filename = "track_export_".date("Y-m-d").".csv";
header("Expires: 0");
header("Cache-control: private");
header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
header("Content-Description: File Transfer");
//header("Content-Type: application/vnd.ms-excel");
header("Content-Type: application/excel");
header("Content-Disposition: attachment; filename=".$filename);

//print $tab_output;
//print $csv_output;
print $file_output;

/*
		$csv_output .= str_replace(",","¸",cleanData($task['issue_title']))
			.",".str_replace(",","¸",cleanData($task['issue_description']))
			.",".str_replace(",","¸",$task['unit'])
			.",".str_replace(",","¸",$task['center'])
			.",".str_replace(",","¸",$task['type'])
			.",".str_replace(",","¸",$task['activity'])
			.",".str_replace(",","¸",$output_topics)
			.",".str_replace(",","¸",$task['priority'])
			.",".str_replace(",","¸",$task['status'])
			.",".str_replace(",","¸",$task['assigned_date'])
			.",".str_replace(",","¸",$task['due_date'])
			.",".str_replace(",","¸",$task['completed_date'])
			.",".str_replace(",","¸",$task['on_time'])
			.",".str_replace(",","¸",$task['grant'])
			.",".str_replace(",","¸",$task['approved'])
			.",".str_replace(",","¸",$task['hours'])
			.",".str_replace(",","¸",cleanData($output_notes))
			."\n";
		$tab_output .= $task['topic']
			."\t".$task['law']
			."\t".$task['level']
			."\t".$output_categories
			."\t".$output_agencies
			."\t".cleanData($task['issue_title'])
			."\t".cleanData($task['issue_description'])
			."\t".$task['pub_date']
			."\t".$task['due_date']
			."\t".$output_impacts
			."\t".cleanData($output_notes)
			."\t".$output_status
			."\t\n";
	
		$csv_outputCOPY .= str_replace(",","¸",$task['topic'])
			.",".str_replace(",","¸",$task['law'])
			.",".str_replace(",","¸",$task['level'])
			.",".str_replace(",","¸",$output_categories)
			.",".str_replace(",","¸",$output_agencies)
			.",".str_replace(",","¸",$task['issue_title'])
			.",".str_replace(",","¸",$task['issue_description'])
			.",".str_replace(",","¸",$task['pub_date'])
			.",".str_replace(",","¸",$task['due_date'])
			.",".str_replace(",","¸",$output_impacts)
			.",".str_replace(",","¸",$output_notes)
			.",".str_replace(",","¸",$output_status)
			."\n";
*/	
?>