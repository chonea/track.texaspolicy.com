<?
error_reporting(E_ALL);
//ini_set("display_errors", 1);

if ($_GET['env'] == 'testing') {
	$true = true;
	require_once('../classes/class.Debugger.php');
	$debug = new Debugger($GLOBALS);
}

require_once("../config.inc");
require_once($_CFG['rootDirAdmin'].'functions/data_connect.inc');
require_once($_CFG['functionWebAdmin'].'functions2.inc');
session_register("userid");
session_register("username");
session_register("userdisplayname");
session_register("administrator");
session_register("editor");
session_register("contributor");

if (strlen($_SESSION['username'])<1) {
	header("Location: ../login/index2.php");
}
if (isset($_REQUEST['action'])) {
	$action = $_REQUEST['action'];
} else {
	$action = 1;
}

if (($_SESSION['administrator'] || $_SESSION['editor']) && !isset($_REQUEST['issue_id'])) {
	$show_batch_actions = true;
} else {
	$show_batch_actions = false;
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?=$_CFG['siteTitle'];?></title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link rel="stylesheet" type="text/css" href="Main.css" />
<link rel="stylesheet" type="text/css" href="Style.css" />
<link rel="stylesheet" type="text/css" href="Forms.css" />
<script language="javascript" src="../javascript/help.js"></script>
<script language="javascript" src="../javascript/sort.js"></script>
<script language="javascript" src="../javascript/cookies.js"></script>

<link rel="stylesheet" type="text/css" href="<?=$_CFG['jsWebAdmin'];?>datepicker/datepicker.css"></link>
<? /*<link href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8/themes/base/jquery-ui.css" rel="stylesheet" type="text/css"/> -- Why does this line crash DW? */ ?>
<link rel="stylesheet" type="text/css" href="../css/jquery-ui.css" />
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.5/jquery.min.js"></script>
<? /*
<script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8/jquery-ui.min.js"></script>
<script src="http://ui.jquery.com/latest/ui/effects.core.js"></script>
<script src="http://ui.jquery.com/latest/ui/effects.slide.js"></script>
*/ ?>
<script language="JavaScript" type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/prototype/1.7.0.0/prototype.js"></script>
<script language="JavaScript" type="text/javascript" src="<?=$_CFG['jsWebAdmin'];?>datepicker/prototype-base-extensions.js"></script>
<script language="JavaScript" type="text/javascript" src="<?=$_CFG['jsWebAdmin'];?>datepicker/prototype-date-extensions.js"></script>
<script language="JavaScript" type="text/javascript" src="<?=$_CFG['jsWebAdmin'];?>datepicker/datepicker.js"></script>
<script language="javascript">
function createPickers() {
	$(document.body).select('input.datetimepicker').each(
		function(e) {
			new Control.DatePicker(e, {
				icon: '<?=$_CFG['jsWebAdmin'];?>datepicker/calendar.png',
				datePicker: true,
				timePicker: false,
				timePickerAdjacent: true,
				use24hrs: false,
				locale: 'en_US',
				onSelect:function(){},
				onHover:function(){}
			});
		}
	);
}
Event.observe(window, 'load', createPickers);
</script>
<? /*
<script src="http://jqueryjs.googlecode.com/files/jquery-1.3.2.min.js" type="text/javascript"></script>
<script src="<?=$_CFG['jsWebAdmin'];?>multiSelect/jquery.bgiframe.min.js" type="text/javascript"></script>
<script src="<?=$_CFG['jsWebAdmin'];?>multiSelect/jquery.multiSelect.js" type="text/javascript"></script>
<link href="<?=$_CFG['jsWebAdmin'];?>multiSelect/jquery.multiSelect.css" rel="stylesheet" type="text/css" />
*/ ?>
<script language="javascript" src="../javascript/track.jquery.js"></script>
</head>
<body>
<form method="post" id="main_form" action="" name="form1">
	<input type="hidden" value="9" id="fieldmax" name="fieldmax" />
	<input type="hidden" name="helpid" id="helpid" value="1">
	<div id="Main">
<? include ('header_nav.inc'); ?>
<?
if (isset($issue_id)) {
	$qry  = "SELECT issue_type_id FROM track_issues WHERE issue_id = '$issue_id'";
	$find = mysql_query($qry, $db) or die (mysql_error());
	$row = mysql_fetch_array($find);
	if ($row['issue_type_id'] == ISSUE_TYPE_PUBLICATION) {
		$view = "publications";
	} elseif ($row['issue_type_id'] == ISSUE_TYPE_CONTACT) {
		$view = "contacts";
	}
}
switch ($view) {
	case 'publications': 
		$viewlangs = "Publication";
		$viewlangp = "Publications";
		$actioncompletelang = "Publish";
		if (!$viewtitle) $viewtitle = "Publications";
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Title', 'type' => 'text', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'type' => 'hidden', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'type' => 'hidden', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'type' => 'textarea', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'publication'			=> array('id' => 'publication', 'label' => 'Publication Type', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'author'					=> array('id' => 'author', 'label' => 'Author', 'type' => 'select', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'type' => 'multiple', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'type' => 'select', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'activity'				=> array('id' => 'activity', 'label' => 'Activity', 'type' => 'select', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'type' => 'multiple', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'priority'				=> array('id' => 'priority', 'label' => 'Priority', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => 'Normal', 'exclude' => ''),
			'status'					=> array('id' => 'status', 'label' => 'Status', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => ISSUE_STATUS_NOT_STARTED),
			'assigned_date'		=> array('id' => 'assigned_date', 'label' => 'Assigned Date', 'type' => 'date', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'draft_due_date'				=> array('id' => 'draft_due_date', 'label' => 'Draft Due Date', 'type' => 'date', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'draft_completed_date'	=> array('id' => 'draft_completed_date', 'label' => 'Draft Completed Date', 'type' => 'date', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'due_date'				=> array('id' => 'due_date', 'label' => 'Projected Published Date', 'type' => 'date', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Published Date', 'type' => 'date', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'on_time'					=> array('id' => 'on_time', 'label' => 'On Time', 'type' => 'select', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'grant'						=> array('id' => 'grant', 'label' => 'Grant', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'approved'				=> array('id' => 'approved', 'label' => 'Concept/Outline Approved', 'type' => 'select', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'hours'						=> array('id' => 'hours', 'label' => 'Hours', 'type' => 'text', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			);
		break;
	case 'contacts': 
		$viewlangs = "Contact";
		$viewlangp = "Contacts";
		$actioncompletelang = "";
		if (!$viewtitle) $viewtitle = "Legislative Contacts";
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Contact', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'contact_office'	=> array('id' => 'contact_office', 'label' => 'Office', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'contact_type'		=> array('id' => 'contact_type', 'label' => 'Type', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Date', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			);
		break;
	case 'centers': 
		if (!$viewtitle) $viewtitle = "Centers";
	case 'all': 
		if (!$viewtitle) $viewtitle = "All Tasks";
	default: 
		$viewlangs = "Task";
		$viewlangp = "Tasks";
		$actioncompletelang = "Complete/Publish";
		if (!$viewtitle) $viewtitle = "Active Tasks";
		$viewform = array(
			'title'						=> array('id' => 'title', 'label' => 'Title', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'created'					=> array('id' => 'created', 'label' => 'Created', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'modified'				=> array('id' => 'modified', 'label' => 'Modified', 'required' => false, 'edit_by' => 'none', 'default' => '', 'exclude' => ''),
			'description'			=> array('id' => 'description', 'label' => 'Description', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'assigned_staff'	=> array('id' => 'staff', 'label' => 'Staff', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'units'						=> array('id' => 'units', 'label' => 'Unit', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'centers'					=> array('id' => 'centers', 'label' => 'Center', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'type'						=> array('id' => 'type', 'label' => 'Type', 'required' => true, 'edit_by' => 'contributor', 'default' => ISSUE_TYPE_TASK, 'exclude' => ISSUE_TYPE_CONTACT.','.ISSUE_TYPE_PUBLICATION),
			'activity'				=> array('id' => 'activity', 'label' => 'Activity', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'topics'					=> array('id' => 'topics', 'label' => 'Topic', 'required' => true, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'priority'				=> array('id' => 'priority', 'label' => 'Priority', 'required' => true, 'edit_by' => 'contributor', 'default' => 'Normal', 'exclude' => ''),
			'status'					=> array('id' => 'status', 'label' => 'Status', 'required' => true, 'edit_by' => 'contributor', 'default' => ISSUE_STATUS_NOT_STARTED),
			'assigned_date'		=> array('id' => 'assigned_date', 'label' => 'Assigned Date', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'due_date'				=> array('id' => 'due_date', 'label' => 'Due Date', 'required' => true, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'completed_date'	=> array('id' => 'completed_date', 'label' => 'Completed Date', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'on_time'					=> array('id' => 'on_time', 'label' => 'On Time', 'required' => false, 'edit_by' => 'editor', 'default' => '', 'exclude' => ''),
			'grant'						=> array('id' => 'grant', 'label' => 'Grant', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'approved'				=> array('id' => 'approved', 'label' => 'Concept/Outline Approved', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			'hours'						=> array('id' => 'hours', 'label' => 'Hours', 'required' => false, 'edit_by' => 'contributor', 'default' => '', 'exclude' => ''),
			);
		break;
}

?>
<? include('issues_searchform_process.inc'); ?>
		<div id="Content">
			<div id="SectionNav">
				<div id="SectionNavMenu">
					<h1><?=$viewtitle?></h1>
					<a href="issues.php?action=1">View <?=$viewlangp?></a>
	<? if ($_SESSION['administrator'] || $_SESSION['editor'] || $_SESSION['contributor']) {?>
					<a href="issues.php?action=2">Add a <?=$viewlangs?></a>
	<? } ?>
	<?
			$qry_search  = "SELECT * FROM track_searches WHERE search_view = '".$view."' AND search_public = '1' ORDER BY search_title";
			$find_search = mysql_query($qry_search, $db) or die (mysql_error());
			if (mysql_num_rows($find_search) > 0) {
				echo "<br /><h1>Searches</h1>";
				while ($row_search = mysql_fetch_array($find_search)) {
					echo '<a href="issues.php?search&search_id='.$row_search['search_id'].'">'.$row_search['search_title'].'</a>';
				}
			}
	?>
	<?
			$qry_search  = "SELECT * FROM track_searches WHERE search_view = '".$view."' AND search_public = '0' AND search_user_id = '".$_SESSION['userid']."' ORDER BY search_title";
			$find_search = mysql_query($qry_search, $db) or die (mysql_error());
			if (mysql_num_rows($find_search) > 0) {
				echo "<br /><h1>My Searches</h1>";
				while ($row_search = mysql_fetch_array($find_search)) {
					echo '<a href="issues.php?search&search_id='.$row_search['search_id'].'">'.$row_search['search_title'].'</a>';
				}
			}
	?>
				</div>
		<?
		if ($show_batch_actions) {
		?>
				<div id="SectionNavActionMenu" class="fixed-element">
					<h1>Actions (<span id="action-total">0</span>)</h1>
      		
					<div class="action-select-all"><input id="action-select-all" type="checkbox" /> <label id="label-action-select-all" for="action-select-all">Select All</label></div>
					<a id="action-delete-selected" href="javascript: return false;">Delete Selected</a>
					<? if ($view != 'contacts') { ?>
					<a id="action-complete-ontime-selected" href="javascript: return false;"><?=$actioncompletelang; ?> Selected (On Time)</a>
					<a id="action-complete-late-selected" href="javascript: return false;"><?=$actioncompletelang; ?> Selected (Late)</a>
					<? } ?>
				</div>
		<?
		}
		?>
			</div>
			<div id="SectionContent">
<?
		switch ($action) {

			case 2:
				include ('issues_forms.inc');
				include ('issues_add.inc');
				break;

			case 3:
				include ('issues_forms.inc');
				include ('issues_add_verify.inc');
				break;

			case 4:
				include ('issues_forms.inc');
				include ('issues_edit.inc');
				break;

			case 5:
				include ('issues_forms.inc');
				include ('issues_edit_verify.inc');
				break;

			case 6:
			case 9:
				include ('issues_summary.inc');
				break;

			case 8:
				include ('issues_summary.inc');
				echo "<p>&nbsp;</p>";
				include ('notes_display.inc');
				echo "<p>&nbsp;</p>";
				include ('documents_display.inc');
				break;

			case 11:
				include ('issues_delete.inc');
				break;

			case 15:
				$issue_on_time = 1;
				include ('issues_update_complete.inc');
				break;

			case 16:
				$issue_on_time = 0;
				include ('issues_update_complete.inc');
				break;

			case 12:
				include ('issues_forms.inc');
				include ('issues_edit.inc');
				break;

			case 13:
				include ('issues_forms.inc');
				include ('issues_copy_verify.inc');
				break;
			/*

			case 7:
				include ('issues_help.inc');
				break;
			
			case 10:
				include ('issues_help_update.inc');
				break;
			case 23:
				include ('issues_assoc_add.inc');
				break;
			
			case 24:
				include ('issues_assoc_insert.inc');
				break;
			
			case 25:
				include ('issues_assoc_delete.inc');
				break;		
			*/		
			
			case 14:
				include ('issues_save_search.inc');
			case 1:
			default:
				include ('issues_display.inc');
				break;

		}
?>
			</div>
		</div>
	</div>
</form>
</body>
</html>