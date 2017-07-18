
<? // $view is previously set ?>

	<input type="hidden" name="order_by_column" id="order_by_column" value="<?
	if (isset($_REQUEST['order_by_column']) && $_REQUEST['order_by_column'] != "") {
		echo $_REQUEST['order_by_column']; 
		$order_by_column = $_REQUEST['order_by_column']; 
	} else { 
		echo "issue_due_date"; 
	}
	?>" />
	<input type="hidden" name="order_by_column_dir" id="order_by_column_dir" value="<? 
	if (isset($_REQUEST['order_by_column_dir']) && $_REQUEST['order_by_column_dir'] != "") { 
		echo $_REQUEST['order_by_column_dir']; 
		$order_by_column_dir = $_REQUEST['order_by_column_dir']; 
	} else { 
		echo "ASC"; 
	} 
	?>" />

<?
/*
if (isset($_REQUEST['searchid']) || isset($_COOKIE[$view.'_search_parameters'])) {

	// display the advanced search form
	$advanced_search = 1;
	include ('issues_searchform.inc');

}
*/
if (isset($_REQUEST['search']) || isset($_COOKIE[$view.'_search_parameters'])) {

	// display the advanced search form
	$advanced_search = 1;
	include ('issues_searchform.inc');

} else {
	
	// display the minimal filter form
	$advanced_search = 0;
	switch ($view) {
	
			case "centers":
			case "publications":
			case "contacts":
			case "all":
				include ('issues_filterform_'.$view.'.inc');
				break;
	
			case "active":
			default:
				include ('issues_filterform_active.inc');
				break;

	} // end switch $view
	
}
/*
?>
<script>
alert(
	'view: <?=$view?>\n'
	+ 'advanced_search: <?=$advanced_search?>\n'
	+ 'search_control_type: <?=$parameters['search_control_type']?>\n'
	+ 'search_results_as: <?=$parameters['search_results_as']?>\n'
);
</script>
*/ ?>
<? if(isset($exec_qry_delete)){ ?>
<table width="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td align="right" width="30%" class="normal">&nbsp;</td>
		<td align="left" width="70%"><img src="<?=$_CFG['imgWebAdmin']?>error.gif" valign="bottom" border="0" />&nbsp;<span class="ok"><i><?=$viewlangs?></i> has been deleted sucessfully</span></td>
	</tr>
</table>
<? } ?>
<? if (isset($exec_qry_insert)) {?>
<table width="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td align="right" width="30%" class="normal">&nbsp;</td>
		<td align="left" width="70%"><img src="<?=$_CFG['imgWebAdmin']?>error.gif" valign="bottom" border=0>&nbsp;<span class="ok"><i><?=$viewlangs?></i> has been added sucessfully</span></td>
	</tr>
</table>
<? } ?>
<? if (isset($exec_qry_copy_insert)) {?>
<table width="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td align="right" width="30%" class="normal">&nbsp;</td>
		<td align="left" width="70%"><img src="<?=$_CFG['imgWebAdmin']?>error.gif" valign="bottom" border=0>&nbsp;<span class="ok"><i><?=$viewlangs?></i> has been copied sucessfully</span></td>
	</tr>
</table>
<? } ?>
<?
if (($advanced_search 
	&& isset($parameters['search_results_as']) && $parameters['search_results_as'] == 'table'
	&& isset($parameters['display_search']) && $parameters['display_search'] == '1')
	|| !$advanced_search) {
	
	// how many rows to show per page
	$rowsPerPage = 25;
	
	// by default we show first page
	$pageNum = 1;
	
	// if $_GET['page'] defined, use it as page number
	if (isset($_GET['page'])) {
		$pageNum = $_GET['page'];
	}
	
	// counting the offset
	$offset = ($pageNum - 1) * $rowsPerPage;

	include ('issues_query.inc');		// creates the query and returns $result

	$rowcount=0;
	?>

	<input type="hidden" name="_lastCol" id="_lastCol" />
	<input type="hidden" name="_lastOrder" id="_lastOrder" />
<!--	<input type="text" style="display: none;" />  -->

	<table cellspacing="0" cellpadding="0" border="0" rules="all" class="Contacts" id="Contacts" style="border-collapse:collapse;">
	<?
	// display the results table header
	switch ($view) {
	
			case "centers":
			case "publications":
			case "contacts":
			case "all":
				include ('issues_viewheader_'.$view.'.inc');
				break;
	
			case "active":
			default:
				include ('issues_viewheader_active.inc');
				break;

	} // end switch $view

	$cat_display = array();
	while($row = mysql_fetch_array($result)) {

		if (isset($cat_id_array) && is_array($cat_id_array)) unset($cat_id_array);
		$cat_ids = $row['issue_unit_ids'].",".$row['issue_center_ids'].",".$row['issue_topic_ids'].",".$row['issue_assigned_staff_ids'];
		$cat_id_array = explode(',',$cat_ids);
		foreach ($cat_id_array as $value) {
			if (!isset($cat_display[$value])) {
				$qry1 = "SELECT cat_title FROM track_categories WHERE cat_id = '".$value."'";
				$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
				if ($row1 = mysql_fetch_array($find1)) {
					$cat_display[$value] = $row1['cat_title'];
				} else {
					$cat_display[$value] = "Error: missing category (".$value.")";
				}
			}
		}
	
		$query2  = "SELECT note_id FROM track_notes WHERE issue_id='".$row['issue_id']."'";
		$result2 = mysql_query($query2) or die('Error, query failed - '.mysql_error());
		$total_notes = mysql_num_rows($result2);
		$notes = $total_notes." note";
		if ($total_notes <> 1) {
			$notes .= "s";
		}
	
		$query3  = "SELECT doc_id FROM track_documents WHERE issue_id='".$row['issue_id']."'";
		$result3 = mysql_query($query3) or die('Error, query failed - '.mysql_error());
		$total_documents = mysql_num_rows($result3);
		$documents = $total_documents." doc";
		if ($total_documents <> 1) {
			$documents .= "s";
		}
	
		if (is_odd($rowcount)) {
			$color_class = "Odd";
		} else {
			$color_class = "";
		}

		//$daysout = getDaysOut($row['due_date'],$row['completed_date']);
		$daysout = $row['sort_date_diff'];
		if ($daysout <= -1) {
			//$cled = "red";
			$status_style = "table-status-overdue";
		} elseif ($daysout <= 7) {
			//$cled = "yellow";
			$status_style = "table-status-due";
		} else {
			//$cled = "green";
			$status_style = "table-status-ok";
		}
	
		?>
		<tr class="<?=$color_class?><? if ($row['issue_status_id'] == $status_completed) { echo ' disabled'; } ?>">
			<? /*<!--<td class="table-status <?=$status_style?>"><center><img src="../images/led_<?=$cled?>.png" border="0"></center></td> */ ?>
			<td class="table-actions" align="center">
		<?
		if ($show_batch_actions) {
		?>
      	<input class="action-checkbox" type="checkbox" name="issue_action_ids[]" value="<?=$row['issue_id']?>" />
		<?
		}
		?>
				<? /* <a class="icon-link icon-complete-ontime" href="issues.php?sid=<?=$sid?>&action=15&issue_id=<?=$row['issue_id']?>" title="Complete On Time">Complete On Time</a>
				<a class="icon-link icon-complete-late" href="issues.php?sid=<?=$sid?>&action=15&issue_id=<?=$row['issue_id']?>" title="Complete Late">Complete On Time</a> */ ?>
				<a class="icon-link icon-edit" href="issues.php?sid=<?=$sid?>&action=4&issue_id=<?=$row['issue_id']?>" title="Edit">Edit</a>
				<a class="icon-link icon-copy" href="issues.php?sid=<?=$sid?>&action=12&issue_id=<?=$row['issue_id']?>" title="Copy">Copy</a>
				<a class="icon-link icon-delete" href="issues.php?sid=<?=$sid?>&action=11&issue_id=<?=$row['issue_id']?>" title="Delete" onClick="return confirm('Are you sure you want to delete this <?=$viewlangs?>: (<?=$row['issue_title']?>)?');">Delete</a>
			</td>
		<?
		if ($view != "contacts") { ?>
			<td class="table-status <?=$status_style?>"></td>
    <? }

	// display the results table row
		switch ($view) {
	
			case "centers":
			case "publications":
			case "contacts":
			case "all":
				include ('issues_viewrow_'.$view.'.inc');
				break;
	
			case "active":
			default:
				include ('issues_viewrow_active.inc');
				break;
	
		} // end switch $view
		?>
		</tr>
		<?
		$rowcount++;
	}
	if ($rowcount == 0) {
		?>
			<tr class="">
				<td colspan="<?=$columncount?>"><p class="error" style="margin:10px;">No results were returned from your query.</p></td>
			</tr>
		<?
	}
	?>
		</table>
	<?
	// how many rows we have in database
	/*
	$query   = "SELECT COUNT(DISTINCT issue_id) AS numrows FROM track_issues WHERE 1=1";

	// Default search
	if (isset($_REQUEST['filter']['title']) && $_REQUEST['filter']['title'] != "") {
		$query  .= " AND issue_title LIKE \"%".$_REQUEST['filter']['title']."%\"";
	}
	if (isset($_REQUEST['filter']['status']) && $_REQUEST['filter']['status'] != "") {
		$query  .= " AND issue_status_id = '".$_REQUEST['filter']['status']."'";
	}
	$result  = mysql_query($query) or die('Error, query 2 failed '.$query);
	$row     = mysql_fetch_array($result, MYSQL_ASSOC);
	$numrows = $row['numrows'];
	*/
	$totalresult = mysql_query($query_issue_search);
	$numrows = mysql_num_rows($totalresult);
	?>
	<table cellspacing="0" rules="all" class="Contacts" border="0" id="Contacts" style="border-collapse:collapse; margin-top:-1px;">
	<?
	include ('print_page_link.inc');
	?>
	</table>
<?
} elseif ($advanced_search 
	&& isset($parameters['search_results_as']) && $parameters['search_results_as'] == 'report'
	&& isset($parameters['display_search']) && $parameters['display_search'] == '1') {

	// print report
	include ('issues_report.inc');
}
?>
<? //=nl2br($query_issue_search)?>