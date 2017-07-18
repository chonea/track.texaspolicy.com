<tr class="Header">
<?
if ($_SESSION['administrator'] || $_SESSION['editor']) {
	$columncount = 14;
?>
	<!--<td width="0%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>-->
	<td width="5%" class="table-actions" align="center">Actions</td>
	<td width="0%"></td>
	<td width="14%"><a href="#" onclick="orderBy('issue_title');">Title</a></td>
	<td width="10%"><a href="#" onclick="orderBy('author');">Author</a></td>
	<td width="10%"><a href="#" onclick="orderBy('publication_type');">Publication Type</a></td>
	<td width="10%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
	<td width="8%"><a href="#" onclick="orderBy('activity');">Activity</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date');">Due /<br />* Draft Due</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('sort_date_diff');">Days Out</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('status');">Status</a></td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('on_time');">On Time</a></td>
	<td width="5%" align="center">Notes</td>
	<td width="5%" align="center">Docs</td>
<?
} else {
	$columncount = 13;
?>
	<!--<td width="0%" align="center"><a href="#" onclick="orderBy('issue_due_date');">#</a></td>-->
	<td width="0%"></td>
	<td width="19%"><a href="#" onclick="orderBy('issue_title');">Title</a></td>
	<td width="10%"><a href="#" onclick="orderBy('author');">Author</a></td>
	<td width="10%"><a href="#" onclick="orderBy('publication_type');">Publication Type</a></td>
	<td width="10%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="8%"><a href="#" onclick="orderBy('unit');">Unit</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
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