
			<td><a href="issues.php?sid=<?=$sid?>&action=8&issue_id=<?=$row['issue_id']?>"><?=$row['issue_title']?></a></td>

			<td><?
			if ($row['issue_assigned_staff_ids'] == '') {
				echo "--";
			} else {
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
							echo "<span class=\"error\"><em>Bad ID (".$value.")</em></span>";
						}
					}
				}
			}
			?></td>

			<td><?
			if ($row['issue_unit_ids'] == '') {
				echo "--";
			} else {
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
			}
			?></td>

			<td><?
			if ($row['issue_center_ids'] == '') {
				echo "--";
			} else {
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
			}
			?></td>

			<td><?
			if ($row['type'] == '') {
				echo "--";
			} else {
				echo $row['type'];
			}
			?></td>

			<td><?
			if ($row['activity'] == '') {
				echo "--";
			} else {
				echo $row['activity'];
			}
			?></td>

			<td align="center"><?
			if ($row['due_date'] == '' || $row['due_date'] == '9999-99-99 99:99:99') { 
				echo "--"; 
			} else { 
				echo $row['due_date']; 
			}
			?></td>

			<td align="center"><?
			if ($row['due_date'] == '' || $row['due_date'] == '9999-99-99 99:99:99') { 
				echo "--"; 
			} else { 
				echo $row['sort_date_diff']; 
			}
			?></td>

			<td align="center"><?
			if ($row['status'] == '') {
				echo "--";
			} else {
				echo $row['status'];
			}
			?></td>

			<td align="center"><?=$row['on_time']?></td>

			<td align="center"><a href="notes.php?sid=<?=$sid?>&action=1&issue_id=<?=$row['issue_id']?>"><?=$notes?></a></td>

			<td align="center"><a href="documents.php?sid=<?=$sid?>&action=1&issue_id=<?=$row['issue_id']?>"><?=$documents?></a></td>