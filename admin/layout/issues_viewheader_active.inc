<tr class="Header">
<?
if ($_SESSION['administrator'] || $_SESSION['editor']) {
	$columncount = 13;
?>
	<!--<td width="0%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>-->
	<td width="5%" class="table-actions" align="center">Actions</td>
	<td width="0%"></td>
	<td width="27%"><a href="#" onclick="orderBy('issue_title');">Task</a></td>
	<td width="8%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
	<td width="8%"><a href="#" onclick="orderBy('type');">Type</a></td>
	<td width="8%"><a href="#" onclick="orderBy('activity');">Activity</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date');">Due /<br />* Draft Due</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date_diff');">Days Out</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('status');">Status</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('on_time');">On Time</a></td>
	<td width="5%" align="center">Notes</td>
	<td width="5%" align="center">Docs</td>
<?
} else {
	$columncount = 12;
?>
	<!--<td width="0%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>-->
	<td width="0%"></td>
	<td width="33%"><a href="#" onclick="orderBy('issue_title');">Task</a></td>
	<td width="8%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
	<td width="8%"><a href="#" onclick="orderBy('type');">Type</a></td>
	<td width="8%"><a href="#" onclick="orderBy('activity');">Activity</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date');">Due /<br />* Draft Due</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date_diff');">Days Out</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('status');">Status</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('on_time');">On Time</a></td>
	<td width="5%" align="center">Notes</td>
	<td width="5%" align="center">Docs</td>
<?
}
?>
</tr>