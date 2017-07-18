<?
//$query_status_update = "UPDATE track_issues SET issue_status_id = '".ISSUE_STATUS_LATE."', issue_on_time = '0' WHERE issue_status_id <> '".ISSUE_STATUS_COMPLETED."' AND issue_due_date < DATE(NOW()) AND issue_type_id <> '".ISSUE_TYPE_CONTACT."'";
$query_status_update = "UPDATE track_issues SET issue_status_id = '".ISSUE_STATUS_LATE."' WHERE issue_status_id <> '".ISSUE_STATUS_COMPLETED."' AND issue_due_date < DATE(NOW()) AND issue_type_id <> '".ISSUE_TYPE_CONTACT."'";
$exec_status_update = mysql_query($query_status_update, $db) or die (mysql_error());
?>