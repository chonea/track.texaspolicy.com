<tr class="Header">
<?
if ($_SESSION['administrator'] || $_SESSION['editor']) {
	$columncount = 10;
?>
	<td width="5%" class="table-actions" align="center">Actions</td>
	<td width="18%"><a href="#" onclick="orderBy('issue_title');">Contact</a></td>
	<td width="18%"><a href="#" onclick="orderBy('contact_office');">Office</a></td>
	<td width="13%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="13%"><a href="#" onclick="orderBy('unit');">Type</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
	<td width="13%">Topics</td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('issue_completed_date');">Date</a></td>
	<td width="5%" align="center">Notes</td>
	<td width="5%" align="center">Docs</td>
<?
} else {
	$columncount = 9;
?>
	<td width="23%"><a href="#" onclick="orderBy('issue_title');">Contact</a></td>
	<td width="18%"><a href="#" onclick="orderBy('contact_office');">Office</a></td>
	<td width="13%"><a href="#" onclick="orderBy('staff');">Staff</a></td>
	<td width="13%"><a href="#" onclick="orderBy('unit');">Type</a></td>
	<td width="5%"><a href="#" onclick="orderBy('center');">Center</a></td>
	<td width="13%">Topics</td>
	<td width="5%" align="center"><a href="#" onclick="orderBy('issue_completed_date');">Date</a></td>
	<td width="5%" align="center">Notes</td>
	<td width="5%" align="center">Docs</td>
<?
}
?>
</tr>