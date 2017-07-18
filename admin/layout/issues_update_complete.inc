<?
include($_CFG['rootDirAdmin'].'functions/data_connect.inc');
//if (isset($issue_id)) {
if (isset($issue_status)) {
	while ($_REQUEST['issue_action_ids']) {
		// update issue
		$query_update = "UPDATE track_issues SET issue_status_id = '".$issue_status."', issue_complete_date = DATE(NOW()) WHERE issue_status_id <> '".ISSUE_STATUS_COMPLETED."' AND issue_due_date < DATE(NOW()) AND issue_type_id <> '".ISSUE_TYPE_CONTACT."'";
//		$exec_update = mysql_query($query_update, $db) or die (mysql_error());
	}
}
$_REQUEST[$action] = 1;
$_REQUEST[$issue_id] = '';
include('issues_display.inc');
?>