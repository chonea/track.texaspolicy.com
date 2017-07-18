<?
function deleteIssue($issue_id) {
	global $query, $db, $_CFG;
	// remove all notes for issue
	$query="DELETE FROM track_notes WHERE issue_id = '$issue_id'";
	$exec_qry_delete = mysql_query($query, $db) or die (mysql_error());
		 
	$qry = "SELECT *
					FROM track_documents
					WHERE issue_id = '$issue_id'
					";
	$find = mysql_query($qry, $db) or die (mysql_error());
	while ($row = mysql_fetch_array($find)) {
		// remove all documents for issue
		unlink($_CFG['uploadDirAdmin'].$row['doc_file']);
		// remove all document associations for issue
		$query="DELETE FROM track_documents WHERE doc_id = '".$row['doc_id']."'";
		$exec_qry_delete = mysql_query($query, $db) or die (mysql_error());
	
	}
	// remove issue
	$query="DELETE FROM track_issues WHERE issue_id = '$issue_id'";
	$exec_qry_delete = mysql_query($query, $db) or die (mysql_error());
}

include($_CFG['rootDirAdmin'].'functions/data_connect.inc');

//echo "<pre>";
//print_r($_REQUEST);
//echo "</pre>";

if (isset($_REQUEST['issue_action_ids'])) {
	foreach ($_REQUEST['issue_action_ids'] as $issue_id) {
		deleteIssue($issue_id);
	}
} elseif (isset($issue_id)) {
	deleteIssue($issue_id);
}
$_REQUEST[$action] = 1;
$_REQUEST[$issue_id] = '';
include('issues_display.inc');
?>