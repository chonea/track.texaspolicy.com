<? require_once($_CFG['rootDirAdmin'].'functions/data_connect.inc'); ?>

<input type="hidden" name="order_by_column" id="order_by_column" value="<? if(isset($_REQUEST['order_by_column']) && $_REQUEST['order_by_column'] != ""){ echo $_REQUEST['order_by_column']; } else { echo "issue_title"; } ?>" />
<input type="hidden" name="order_by_column_dir" id="order_by_column_dir" value="<? if(isset($_REQUEST['order_by_column_dir']) && $_REQUEST['order_by_column_dir'] != ""){ echo $_REQUEST['order_by_column_dir']; } else { echo "ASC"; } ?>" />

<?
if (isset($_REQUEST['search']) || isset($_COOKIE['search_parameters'])) { 

//	include ('issues_searchform.inc');
	$advanced_search = true;

} else {

	$advanced_search = false;
?>
<table class="BoxSearch" id="SearchContact" width="100%">
	<tr>
		<td><strong>Filter </strong> &nbsp; <em>(key phrase in Task)</em></td>
		<td><strong>Center</strong></td>
	</tr>
	<tr>
		<td><input name="filter_title" type="text" id="filter_title" value="<? if ($_REQUEST['filter_title']<>"") {echo $_REQUEST['filter_title'];}  ?>" class="field"/></td>
		<td>
			<select name="filter_status" id="filter_status" class="field">
				<option value="">All</option>
				<?
				$qry1 = "SELECT * FROM track_categories WHERE cat_type = 'center' ORDER BY cat_title";
				$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
				while($row1 = mysql_fetch_array($find1)) {
					if ($_REQUEST['filter_status'] != 'Completed') {
						echo "<option value=\"".$row1['cat_id']."\"";
						if ($_REQUEST['filter_status'] == $row1['cat_id']) echo " selected";
						echo ">".$row1['cat_title']."</option>";
					}
				}
				?>
			</select>
		</td>
		<td align="right">
			<input type="submit" name="btnFilter" value="Search" id="btnFilter" class="smallbutton"/>
			<input type="reset" name="btnClearFilter" value="Clear" id="btnClearFilter" class="smallbutton" onclick="document.getElementById('filter_title').value=''; document.getElementById('filter_status').options[0].selected=true; return false;"/>
			<input type="submit" name="btnAdvancedSearch" value="New Advanced Search &raquo;" id="btnAdvancedSearch" class="smallbutton" onclick="javascript: form1.action='issues.php?search'"/>
		</td>
	</tr>
</table><?
}
?>


<?
	if($exec_qry_delete){
	?>
<table width="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td align="right" width="30%" class="normal">&nbsp;</td>
		<td align="left">
			<img src="<?=$_CFG['imgWebAdmin']?>error.gif" valign="bottom" border="0" />&nbsp;<span class="error"><i>Task</i> has been sucessfully deleted.</span>
		</td>
	</tr>
</table><?
	}
?>

<?
if (($advanced_search 
	&& isset($parameters['search_results_as']) && $parameters['search_results_as'] == 'table'
	&& isset($parameters['display_search']) && $parameters['display_search'] == '1')
	|| !$advanced_search) {

	function is_odd($number) {
		 return $number & 1; // 0 = even, 1 = odd
	}
	
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
	
	$odd_counter=0;
	?>
	<input name="_lastCol" id="_lastCol" type="hidden" />
	<input name="_lastOrder" id="_lastOrder" type="hidden" />
	<input type="text" style="display: none;" />
	<table cellspacing="0" rules="all" class="Contacts" border="1" id="Contacts" style="border-collapse:collapse;">
		<tr style="font-weight:bold;" class="Odd2">
	<?
		if ($_SESSION['administrator'] || $_SESSION['editor']) {
			$col_counter = 14;
	?>
			<td width="2%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>
			<td width="23%"><a href="#" onclick="orderBy('issue_title');">Task</a></td>
			<td width="8%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
			<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
			<td width="8%"><a href="#" onclick="orderBy('center');">Center</a></td>
			<td width="8%"><a href="#" onclick="orderBy('type');">Type</a></td>
			<td width="8%"><a href="#" onclick="orderBy('activity');">Activity</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('issue_due_date');">Due</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('issue_submitted_date');">Submitted</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('status');">Status</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('on_time');">On Time</a></td>
			<td width="5%" align="center">Notes</td>
			<td width="5%" align="center">Docs</td>
			<td width="5%" align="center">Actions</td>
	<?
		} else {
			$col_counter = 13;
	?>
			<td width="2%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>
			<td width="28%"><a href="#" onclick="orderBy('issue_title');">Task</a></td>
			<td width="8%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
			<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
			<td width="8%"><a href="#" onclick="orderBy('center');">Center</a></td>
			<td width="8%"><a href="#" onclick="orderBy('type');">Type</a></td>
			<td width="8%"><a href="#" onclick="orderBy('activity');">Activity</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('issue_due_date');">Due</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('issue_submitted_date');">Submitted</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('status');">Status</a></td>
			<td width="5%" align="center"><a href="#" onclick="orderBy('on_time');">On Time</a></td>
			<td width="5%" align="center">Notes</td>
			<td width="5%" align="center">Docs</td>
	<?
		}
	?>
		</tr>
	<?
	$cat_display = array();
	while($row = mysql_fetch_array($result))
	{
		if (is_array($cat_id_array)) unset($cat_id_array);
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
	
		if (is_odd($odd_counter)) {
			$color_class = "Odd";
		}
		else {
			$color_class = "";
		}

		$daysout = getDaysOut($row['due_date']);
		if ($daysout <= 0) {
			$cled = "red";
		} elseif ($daysout <= 30) {
			$cled = "yellow";
		} else {
			$cled = "green";
		}
	
		?>
		<tr class="<?=$color_class?>">

			<td><center><img src="../images/led_<?=$cled?>.png" border="0"></center></td>

			<td><a href="issues.php?sid=<?=$sid?>&action=8&issue_id=<?=$row['issue_id']?>"><?=$row['issue_title']?></a></td>

			<td><?
			$first = true;
			$id_set = explode(',',$row['issue_assigned_staff_ids']);
			foreach ($id_set as $value) {
				if ($value != '') {
					if ($first) {
						$first = false;
					} else {
						echo "<br />";
					}
					$qry1 = "SELECT user_name FROM track_users WHERE user_id = '".$value."'";
					$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
					if ($row1 = mysql_fetch_array($find1)) {
						echo $row1['user_name'];
					} else {
						echo "--";
					}
				}
			}
			?></td>

			<td><?
			$first = true;
			$id_set = explode(',',$row['issue_unit_ids']);
			foreach ($id_set as $value) {
				if ($value != '') {
					if ($first) {
						$first = false;
					} else {
						echo "<br />";
					}
					echo $cat_display[$value];
				}
			}
			?></td>

			<td><?
			$first = true;
			$id_set = explode(',',$row['issue_center_ids']);
			foreach ($id_set as $value) {
				if ($value != '') {
					if ($first) {
						$first = false;
					} else {
						echo "<br />";
					}
					echo $cat_display[$value];
				}
			}
			?></td>

			<td><?
			$first = true;
			$id_set = explode(',',$row['issue_type_ids']);
			foreach ($id_set as $value) {
				if ($value != '') {
					if ($first) {
						$first = false;
					} else {
						echo "<br />";
					}
					echo $cat_display[$value];
				}
			}
			?></td>

			<td><?
			$first = true;
			$id_set = explode(',',$row['issue_activity_ids']);
			foreach ($id_set as $value) {
				if ($value != '') {
					if ($first) {
						$first = false;
					} else {
						echo "<br />";
					}
					echo $cat_display[$value];
				}
			}
			?></td>

			<td align="center"><? if ($row['due_date']) { echo $row['due_date']; } else { echo "---"; }?></td>

			<td align="center"><? if ($row['submitted_date']) { echo $row['submitted_date']; } else { echo "---"; }?></td>

			<td align="center"><?=$row['status']?></td>

			<td align="center"><?=$row['on_time']?></td>

			<td align="center"><a href="notes.php?sid=<?=$sid?>&action=1&issue_id=<?=$row['issue_id']?>"><?=$notes?></a></td>

			<td align="center"><a href="documents.php?sid=<?=$sid?>&action=1&issue_id=<?=$row['issue_id']?>"><?=$documents?></a></td>

	<? if ($_SESSION['administrator'] || $_SESSION['editor']) {?>
			<td align="center">
				<a href="issues.php?sid=<?=$sid?>&action=4&issue_id=<?=$row['issue_id']?>">Edit</a> |
				<a href="issues.php?sid=<?=$sid?>&action=11&issue_id=<?=$row['issue_id']?>" onClick="return confirm('Are you sure you want to delete this task: (<?=$row['issue_title']?>)?');">Delete</a>
			</td>
	<? } ?>

		</tr>
		<?
	
		$odd_counter++;
	}
	if ($odd_counter == 0) {
		?>
			<tr class="">
				<td colspan="<?=$col_counter?>"><p class="error" style="margin:10px;">No results were returned from your query.</p></td>
			</tr>
		<?
	}
	?>
		</table>
	<?
	// how many rows we have in database
	
	$query   = "SELECT COUNT(DISTINCT issue_id) AS numrows FROM track_issues WHERE 1=1";

	// Default search
	if ($_REQUEST['filter_title'] != "") {
		$query  .= " AND issue_title LIKE \"%".$_REQUEST['filter_title']."%\"";
	}
	if ($_REQUEST['filter_status']) {
		$query  .= " AND issue_status_id = '".$_REQUEST['filter_status']."'";
	}
	
	$result  = mysql_query($query) or die('Error, query 2 failed '.$query);
	$row     = mysql_fetch_array($result, MYSQL_ASSOC);
	$numrows = $row['numrows'];
	?>
	<table cellspacing="0" rules="all" class="Contacts" border="1" id="Contacts" style="border-collapse:collapse;">
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