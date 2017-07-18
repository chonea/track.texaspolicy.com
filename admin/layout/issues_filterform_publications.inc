<script type="text/javascript">
window.onload = function() {
	document.getElementById('filter_title').focus();
}; 
</script>
<table class="BoxSearch" id="SearchContact" width="100%">
	<tr>
		<td align="left">
			<table border="0" cellpadding="0" cellspacing="10">
				<tr>
					<td><strong>Filter </strong> &nbsp; <em>(key phrase in Title)</em></td>
					<? /* <td><strong>Publication Type</strong></td> */ ?>
					<td><strong>Center</strong></td>
					<td><strong>Staff</strong></td>
					<td><strong>Grant</strong></td>
					<td><strong>Status</strong></td>
					<td><strong>Range</strong></td>
					<td><strong>Due</strong></td>
					<td><strong>Publication Date</strong></td>
				</tr>
				<tr>
					<td><input name="filter[title]" type="text" id="filter_title" value="<? if (isset($_REQUEST['filter']['title']) && $_REQUEST['filter']['title'] <> "") {echo $_REQUEST['filter']['title'];}  ?>" class="searchfield"/></td>
					<? /*
					<td>
						<select name="filter[publication_type]" id="filter_publication_type" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<?
							$qry1 = "SELECT * FROM track_categories WHERE cat_type = 'publication' ORDER BY cat_title";
							$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
							while($row1 = mysql_fetch_array($find1)) {
								echo "<option value=\"".$row1['cat_id']."\"";
								if ($_REQUEST['filter']['publication_type'] == $row1['cat_id']) echo " selected";
								echo ">".$row1['cat_title']."</option>";
							}
							?>
						</select>
					</td>
					<td>
						<select name="filter[unit]" id="filter_unit" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<?
							$qry1 = "SELECT * FROM track_categories WHERE cat_type = 'unit' ORDER BY cat_title";
							$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
							while($row1 = mysql_fetch_array($find1)) {
								echo "<option value=\"".$row1['cat_id']."\"";
								if ($_REQUEST['filter']['unit'] == $row1['cat_id']) echo " selected";
								echo ">".$row1['cat_title']."</option>";
							}
							?>
						</select>
					</td>
					*/ ?>
					<td>
						<select name="filter[center]" id="filter_center" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<?
							$qry1 = "SELECT * FROM track_categories WHERE cat_type = 'center' ORDER BY cat_title";
							$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
							while($row1 = mysql_fetch_array($find1)) {
								echo "<option value=\"".$row1['cat_id']."\"";
								if ($_REQUEST['filter']['center'] == $row1['cat_id']) echo " selected";
								echo ">".$row1['cat_title']."</option>";
							}
							?>
						</select>
					</td>
					<td>
						<select name="filter[assigned_staff]" id="filter_assigned_staff" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<?
							$qry1 = "SELECT * FROM track_users WHERE user_type <> '5' ORDER BY user_name";
							$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
							while($row1 = mysql_fetch_array($find1)) {
								echo "<option value=\"".$row1['user_id']."\"";
								if ($_REQUEST['filter']['assigned_staff'] == $row1['user_id']) echo " selected";
								echo ">".$row1['user_name']."</option>";
							}
							?>
						</select>
					</td>
					<td>
						<select name="filter[grant]" id="filter_grant" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<option value="grant_yes"<? if ($_REQUEST['filter']['grant'] == "grant_yes") echo " selected"; ?>>Grant</option>
							<option value="grant_no"<? if ($_REQUEST['filter']['grant'] == "grant_no") echo " selected"; ?>>No Grant</option>
						</select>
					</td>
					<td>
						<select name="filter[status]" id="filter_status" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<?
							$qry1 = "SELECT * FROM track_categories WHERE cat_type = 'status' AND cat_id <> '".$status_completed."' ORDER BY cat_title";
							$find1 = mysql_query($qry1, $db) or die (mysql_error($qry1));
							while($row1 = mysql_fetch_array($find1)) {
								if ($_REQUEST['filter']['status'] != 'Completed') {
									echo "<option value=\"".$row1['cat_id']."\"";
									if (isset($_REQUEST['filter']['status']) && $_REQUEST['filter']['status'] == $row1['cat_id']) echo " selected";
									echo ">".$row1['cat_title']."</option>";
								}
							}
							?>
						</select>
					</td>
					<td><?
						if ($_REQUEST['filter']['publication_range'] == "") {
							$_REQUEST['filter']['publication_range'] = "current";
						}
						?>
						<select name="filter[publication_range]" id="filter_publication_range" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="current"<? if ($_REQUEST['filter']['publication_range'] == "current" or $_REQUEST['filter']['publication_range'] == "") echo " selected"; ?>>Current</option>
							<option value="ytd"<? if ($_REQUEST['filter']['publication_range'] == "ytd") echo " selected"; ?>>YTD</option>
							<option value="lastyear"<? if ($_REQUEST['filter']['publication_range'] == "lastyear") echo " selected"; ?>>Last Year</option>
							<option value="all"<? if ($_REQUEST['filter']['publication_range'] == "all") echo " selected"; ?>>All</option>
						</select>
					</td>
					<td>
						<select name="filter[due_range]" id="filter_due_range" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<option value="pastdue"<? if ($_REQUEST['filter']['due_range'] == "pastdue") echo " selected"; ?>>Past Due</option>
							<option value="thisweek"<? if ($_REQUEST['filter']['due_range'] == "thisweek") echo " selected"; ?>>Next 7 Days</option>
							<option value="thismonth"<? if ($_REQUEST['filter']['due_range'] == "thismonth") echo " selected"; ?>>Next 30 Days</option>
							<option value="nextmonth"<? if ($_REQUEST['filter']['due_range'] == "nextmonth") echo " selected"; ?>>Next 31-60 Days</option>
							<option value="next60"<? if ($_REQUEST['filter']['due_range'] == "next60") echo " selected"; ?>>Next 60 Days</option>
						</select>
					</td>
					<td>
						<select name="filter[completed_range]" id="filter_completed_range" class="searchfield" onchange="javascript:setfiltercookie('<?=$view?>', this);this.form.submit();">
							<option value="">All</option>
							<option value="lastyear"<? if ($_REQUEST['filter']['completed_range'] == "lastyear") echo " selected"; ?>>Last Year</option>
							<option value="yeartodate"<? if ($_REQUEST['filter']['completed_range'] == "yeartodate") echo " selected"; ?>>YTD</option>
							<option value="fullyear"<? if ($_REQUEST['filter']['completed_range'] == "fullyear") echo " selected"; ?>>Full Year</option>
							<option value="nextyear"<? if ($_REQUEST['filter']['completed_range'] == "nextyear") echo " selected"; ?>>Next Year</option>
						</select>
					</td>
				</tr>
			</table>
		</td>
		<td align="right" valign="bottom">
			<script type="text/javascript">
			function clearFilter() {
				document.getElementById('filter_title').value=''; 
//				document.getElementById('filter_publication_type').options[0].selected=true; 
				document.getElementById('filter_unit').options[0].selected=true; 
				document.getElementById('filter_center').options[0].selected=true; 
				document.getElementById('filter_publication_range').options[0].selected=true; 
				document.getElementById('filter_assigned_staff').options[0].selected=true; 
				document.getElementById('filter_status').options[0].selected=true; 
				document.getElementById('filter_due_range').options[0].selected=true; 
				document.getElementById('filter_grant').options[0].selected=true; 
				deletecookie('filter_<?=$view?>');
			}
			</script>
			<input type="submit" name="btnFilter" value="Simple Search" id="btnFilter" class="smallbutton" onclick="javascript:setfiltercookie('<?=$view?>', document.getElementById('filter_title'));this.form.submit();"/>
			<input type="submit" name="btnClearFilter" value="Clear" id="btnClearFilter" class="smallbutton" onclick="clearFilter(); return true;"/>
			<input type="submit" name="btnAdvancedSearch" value="Advanced Search &raquo;" id="btnAdvancedSearch" class="smallbutton" onclick="javascript:setfiltercookie('<?=$view?>', document.getElementById('filter_title'));form1.action='issues.php?search'"/>
		</td>
	</tr>
</table>