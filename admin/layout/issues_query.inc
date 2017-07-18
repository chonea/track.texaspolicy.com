<?
	$query_issue_search  = "SELECT *, 
		IF (i.issue_assigned_staff_ids = '', '', (SELECT u.user_name FROM track_users AS u WHERE u.user_id = i.issue_assigned_staff_ids)) AS staff, 
		IF (i.issue_created_date = '0000-00-00 00:00:00', '', DATE_FORMAT(i.issue_created_date, '%m/%d/%Y')) AS created_date, 
		IF (i.issue_created_by = 0, '', (SELECT u.user_name FROM track_users AS u WHERE u.user_id = i.issue_created_by)) AS created_by, 
		IF (i.issue_last_modified_date = '0000-00-00 00:00:00', '', DATE_FORMAT(i.issue_last_modified_date, '%m/%d/%Y')) AS modified_date, 
		IF (i.issue_last_modified_by = 0, '', (SELECT u.user_name FROM track_users AS u WHERE u.user_id = i.issue_last_modified_by)) AS modified_by, 
		IF (i.issue_assigned_date = '0000-00-00 00:00:00', '', DATE_FORMAT(i.issue_assigned_date, '%m/%d/%Y')) AS assigned_date, 
		IF (i.issue_due_date = '0000-00-00 00:00:00', IF (i.issue_draft_due_date = '0000-00-00 00:00:00', '--/--/----', DATE_FORMAT(i.issue_draft_due_date, '%m/%d/%Y *')), DATE_FORMAT(i.issue_due_date, '%m/%d/%Y')) AS due_date,
		IF (i.issue_due_date = '0000-00-00 00:00:00', 
			IF (i.issue_draft_due_date = '0000-00-00 00:00:00',  
				IF (i.issue_completed_date = '0000-00-00 00:00:00', 
					'9999-99-99 99:99:99', 
					DATE_FORMAT(i.issue_completed_date, '%Y-%m-%d 00:00:00')
				), 
				DATE_FORMAT(i.issue_draft_due_date, '%Y-%m-%d 00:00:00')
			), 
			DATE_FORMAT(i.issue_due_date, '%Y-%m-%d 00:00:00')
		) AS sort_date,
		IF (i.issue_due_date = '0000-00-00 00:00:00', 
			IF (i.issue_draft_due_date = '0000-00-00 00:00:00', 
				DATEDIFF('9999-99-99 99:99:99',NOW()), 
				DATEDIFF(DATE_FORMAT(i.issue_draft_due_date, '%Y-%m-%d 00:00:00'),NOW())
			), 
			DATEDIFF(DATE_FORMAT(i.issue_due_date, '%Y-%m-%d 00:00:00'),NOW())
		) AS sort_date_diff,
		IF (i.issue_completed_date = '0000-00-00 00:00:00', '', DATE_FORMAT(i.issue_completed_date, '%m/%d/%Y')) AS completed_date,
		IF (i.issue_contact_office_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_contact_office_id)) AS contact_office, 
		IF (i.issue_contact_type_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_contact_type_id)) AS contact_type, 
		IF (i.issue_unit_ids = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_unit_ids)) AS unit, 
		IF (i.issue_center_ids = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_center_ids)) AS center, 
		IF (i.issue_type_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_type_id)) AS type, 
		IF (i.issue_publication_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_publication_id)) AS publication_type, 
		IF (i.issue_author_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_author_id)) AS author, 
		IF (i.issue_status_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_status_id)) AS status,
		IF (i.issue_grant_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_grant_id)) AS grant_name, 
		IF (i.issue_approved = '0', 'Not Approved', IF (i.issue_approved = '1', 'Approved', '--')) AS approved, 
		IF (i.issue_on_time = '0', 'Late', IF (i.issue_on_time = '1', 'On Time', '--')) AS on_time, 
		IF (i.issue_priority = '', '--', i.issue_priority) AS priority, 
		IF (i.issue_hours = 0, '--', i.issue_hours) AS hours, 
		IF (i.issue_activity_id = 0, '', (SELECT c.cat_title FROM track_categories AS c WHERE c.cat_id = i.issue_activity_id)) AS activity 
		FROM track_issues AS i 
		WHERE 1=1";

	if ($view != "all" && $view != "publications" && $view != "contacts") {
		$query_issue_search  .= " AND i.issue_status_id <> '".ISSUE_STATUS_COMPLETED."'";
	}
	if ($view != "contacts") {
		$query_issue_search  .= " AND i.issue_type_id <> '".ISSUE_TYPE_CONTACT."'";
	} else {
		$query_issue_search  .= " AND i.issue_type_id = '".ISSUE_TYPE_CONTACT."'";
	}
//	if ($view != "publications") {
//		$query_issue_search  .= " AND i.issue_type_id <> '".ISSUE_TYPE_PUBLICATION."'";
//	} else
	if ($view == "publications") {
		$query_issue_search  .= " AND i.issue_type_id = '".ISSUE_TYPE_PUBLICATION."'";
		if (!isset($_REQUEST['filter']['publication_range'])) {
			// default to current
			/*
			$query_issue_search  .= " AND issue_posted_date = '0000-00-00 00:00:00'";
			$query_issue_search  .= " AND issue_completed_date = '0000-00-00 00:00:00'";
			*/
		}
	}

/*** SIMPLE SEARCH *******************************************************************************************************************************************/	

	if (!isset($advanced_search) || $advanced_search == '') {

		// Default search
		if (isset($_REQUEST['filter']['title']) && $_REQUEST['filter']['title'] != "") {
			$query_issue_search  .= " AND i.issue_title LIKE \"%".$_REQUEST['filter']['title']."%\"";
		}
		
		// Category searches
		if (isset($_REQUEST['filter']['center']) && $_REQUEST['filter']['center'] != "") {
			$query_issue_search  .= " AND FIND_IN_SET('".$_REQUEST['filter']['center']."', i.issue_center_ids)";
		}
		if (isset($_REQUEST['filter']['unit']) && $_REQUEST['filter']['unit'] != "") {
			$query_issue_search  .= " AND FIND_IN_SET('".$_REQUEST['filter']['unit']."', i.issue_unit_ids)";
		}
		if (isset($_REQUEST['filter']['publication_type']) && $_REQUEST['filter']['publication_type'] != "") {
			$query_issue_search  .= " AND i.issue_publication_id = '".$_REQUEST['filter']['publication_type']."'";
		}
		if (isset($_REQUEST['filter']['publication_range'])) {
			if ($_REQUEST['filter']['publication_range'] == "current") {
				// posted date null
				/*
				$query_issue_search  .= " AND i.issue_posted_date = '0000-00-00 00:00:00'";
				*/
				// completed date null
				$query_issue_search  .= " AND i.issue_completed_date = '0000-00-00 00:00:00'";
			} elseif ($_REQUEST['filter']['publication_range'] == "ytd") {
				// posted date null or this year
				/*
				$query_issue_search  .= " AND (";
				$query_issue_search  .= "(i.issue_posted_date = '0000-00-00 00:00:00')";
				$query_issue_search  .= " OR ";
				$query_issue_search  .= "(i.issue_posted_date >= '".date('Y')."-01-01 00:00:00')";
				$query_issue_search  .= ")";
				*/
				// completed date null or this year
				$query_issue_search  .= " AND (";
				$query_issue_search  .= "(i.issue_completed_date = '0000-00-00 00:00:00')";
				$query_issue_search  .= " OR ";
				$query_issue_search  .= "(i.issue_completed_date >= '".date('Y')."-01-01 00:00:00')";
				$query_issue_search  .= ")";
			} elseif ($_REQUEST['filter']['publication_range'] == "lastyear") {
				// posted date null or last year
				/*
				$query_issue_search  .= " AND (";
				$query_issue_search  .= "(i.issue_posted_date >= '".(date('Y')-1)."-01-01 00:00:00')";
				$query_issue_search  .= " AND ";
				$query_issue_search  .= "(i.issue_posted_date < '".date('Y')."-01-01 00:00:00')";
				$query_issue_search  .= ")";
				*/
				// completed date null or last year
				$query_issue_search  .= " AND (";
				$query_issue_search  .= "(i.issue_completed_date >= '".(date('Y')-1)."-01-01 00:00:00')";
				$query_issue_search  .= " AND ";
				$query_issue_search  .= "(i.issue_completed_date < '".date('Y')."-01-01 00:00:00')";
				$query_issue_search  .= ")";
			}
		}
		if (isset($_REQUEST['filter']['due_range'])) {
			if ($_REQUEST['filter']['due_range'] == "pastdue") {
				$query_issue_search  .= " AND i.issue_due_date < NOW()";
			} elseif ($_REQUEST['filter']['due_range'] == "thisweek") {
				$query_issue_search  .= " AND i.issue_due_date < '".date('Y-m-d H:i:s',strtotime('+ 7 days',strtotime(date('Y-m-d'))))."'";
			} elseif ($_REQUEST['filter']['due_range'] == "thismonth") {
				$query_issue_search  .= " AND i.issue_due_date < '".date('Y-m-d H:i:s',strtotime('+ 30 days',strtotime(date('Y-m-d'))))."'";
			} elseif ($_REQUEST['filter']['due_range'] == "nextmonth") {
				$query_issue_search  .= " AND (";
				$query_issue_search  .= "(i.issue_due_date >= '".date('Y-m-d H:i:s',strtotime('+ 30 days',strtotime(date('Y-m-d'))))."')";
				$query_issue_search  .= " AND ";
				$query_issue_search  .= "(i.issue_due_date < '".date('Y-m-d H:i:s',strtotime('+ 60 days',strtotime(date('Y-m-d'))))."')";
				$query_issue_search  .= ")";
			} elseif ($_REQUEST['filter']['due_range'] == "next60") {
				$query_issue_search  .= " AND i.issue_due_date < '".date('Y-m-d H:i:s',strtotime('+ 60 days',strtotime(date('Y-m-d'))))."'";
			}
		}
		if (isset($_REQUEST['filter']['contact_office']) && $_REQUEST['filter']['contact_office'] != "") {
			$query_issue_search  .= " AND i.issue_contact_office_id = '".$_REQUEST['filter']['contact_office']."'";
		}
		if (isset($_REQUEST['filter']['type']) && $_REQUEST['filter']['type'] != "") {
			$query_issue_search  .= " AND i.issue_type_id = '".$_REQUEST['filter']['type']."'";
		}
		if (isset($_REQUEST['filter']['status']) && $_REQUEST['filter']['status'] != "") {
			$query_issue_search  .= " AND i.issue_status_id = '".$_REQUEST['filter']['status']."'";
		}
		if (isset($_REQUEST['filter']['grant'])) {
			if ($_REQUEST['filter']['grant'] == "grant_yes") {
				$query_issue_search  .= " AND i.issue_grant_id <> 0";
			} elseif ($_REQUEST['filter']['grant'] == "grant_no") {
				$query_issue_search  .= " AND i.issue_grant_id = 0";
			}
		}
		
		// User search
		if (isset($_REQUEST['filter']['assigned_staff']) && $_REQUEST['filter']['assigned_staff'] != "") {
			$query_issue_search  .= " AND FIND_IN_SET('".$_REQUEST['filter']['assigned_staff']."', i.issue_assigned_staff_ids)";
		}
		
/*** ADVANCED SEARCH *****************************************************************************************************************************************/	

	} else {
		// Advanced search
	
		if (isset($parameters['search_control_type'])) {
			$search_control_type = $parameters['search_control_type'];
		} else {
			$search_control_type = "AND";
		}

		if ($search_control_type == "OR") {
			$query_issue_search .= " AND (1<>1";
		}

		if (isset($parameters['search_title']) && $parameters['search_title'] != "") {
			$query_issue_search  .= " ".$search_control_type." i.issue_title LIKE \"%".$parameters['search_title']."%\"";
		}

		if (isset($parameters['search_description']) && $parameters['search_description'] != "") {
			$query_issue_search  .= " ".$search_control_type." i.issue_description LIKE \"%".$parameters['search_description']."%\"";
		}

		if (isset($parameters['search_priority']) && $parameters['search_priority'] != "") {
			$query_issue_search  .= " ".$search_control_type." i.issue_priority = '".$parameters['search_priority']."'";
		}

		if (isset($parameters['search_approved']) && $parameters['search_approved'] != "") {
			$query_issue_search  .= " ".$search_control_type." i.issue_approved = '".$parameters['search_approved']."'";
		}

		if (isset($parameters['search_on_time']) && $parameters['search_on_time'] != "") {
			$query_issue_search  .= " ".$search_control_type." i.issue_on_time = '".$parameters['search_on_time']."'";
		}

		// this is a multi-capable field
		if (is_array($parameters['search_assigned_staff'])) {
			foreach ($parameters['search_assigned_staff'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." FIND_IN_SET('".$selection."', i.issue_assigned_staff_ids)";
				}
			}
		}

		// this is a multi-capable field
		if (is_array($parameters['search_unit'])) {
			foreach ($parameters['search_unit'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." FIND_IN_SET('".$selection."', i.issue_unit_ids)";
				}
			}
		}

		// this is a multi-capable field
		if (is_array($parameters['search_center'])) {
			foreach ($parameters['search_center'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." FIND_IN_SET('".$selection."', i.issue_center_ids)";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_type'])) {
			foreach ($parameters['search_type'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_type_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_publication'])) {
			foreach ($parameters['search_publication'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_publication_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_contact_office'])) {
			foreach ($parameters['search_contact_office'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_contact_office_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_contact_type'])) {
			foreach ($parameters['search_contact_type'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_contact_type_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable field
		if (is_array($parameters['search_topic'])) {
			foreach ($parameters['search_topic'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." FIND_IN_SET('".$selection."', i.issue_topic_ids)";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_activity'])) {
			foreach ($parameters['search_activity'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_activity_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_grant'])) {
			foreach ($parameters['search_grant'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_grant_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_author'])) {
			foreach ($parameters['search_author'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_author_id = '".$selection."'";
				}
			}
		}

		// this is a multi-capable search on a single id field
		if (is_array($parameters['search_status'])) {
			foreach ($parameters['search_status'] as $selection) {
				if ($selection != '' && $selection != 0) {
					$query_issue_search  .= " ".$search_control_type." i.issue_status_id = '".$selection."'";
				}
			}
		}

		if (isset($parameters['search_assigned_date_from']) && $parameters['search_assigned_date_from'] != "") {
			$query_issue_search  .= " ".$search_control_type." ";
			if (isset($parameters['search_assigned_date_to']) && $parameters['search_assigned_date_to'] != "") {
				$query_issue_search  .= "(";
			}
			$query_issue_search  .= "i.issue_assigned_date >= '".convertMDYtoYMD($parameters['search_assigned_date_from'])."'";
		}
		if (isset($parameters['search_assigned_date_to']) && $parameters['search_assigned_date_to'] != "") {
			if (isset($parameters['search_assigned_date_from']) && $parameters['search_assigned_date_from'] != "") {
				$query_issue_search  .= " AND i.issue_assigned_date <= '".convertMDYtoYMD($parameters['search_assigned_date_to'])."')";
			} else {
				$query_issue_search  .= " ".$search_control_type." i.issue_assigned_date <= '".convertMDYtoYMD($parameters['search_assigned_date_to'])."'";
			}
		}

		if (isset($parameters['search_due_date_from']) && $parameters['search_due_date_from'] != "") {
			$query_issue_search  .= " ".$search_control_type." ";
			if (isset($parameters['search_due_date_to']) && $parameters['search_due_date_to'] != "") {
				$query_issue_search  .= "(";
			}
			$query_issue_search  .= "i.issue_due_date >= '".convertMDYtoYMD($parameters['search_due_date_from'])."'";
		}
		if (isset($parameters['search_due_date_to']) && $parameters['search_due_date_to'] != "") {
			if (isset($parameters['search_due_date_from']) && $parameters['search_due_date_from'] != "") {
				$query_issue_search  .= " AND i.issue_due_date <= '".convertMDYtoYMD($parameters['search_due_date_to'])."')";
			} else {
				$query_issue_search  .= " ".$search_control_type." i.issue_due_date <= '".convertMDYtoYMD($parameters['search_due_date_to'])."'";
			}
		}

		if (isset($parameters['search_completed_date_from']) && $parameters['search_completed_date_from'] != "") {
			$query_issue_search  .= " ".$search_control_type." ";
			if (isset($parameters['search_completed_date_to']) && $parameters['search_completed_date_to'] != "") {
				$query_issue_search  .= "(";
			}
			$query_issue_search  .= "i.issue_completed_date >= '".convertMDYtoYMD($parameters['search_completed_date_from'])."'";
		}
		if (isset($parameters['search_completed_date_to']) && $parameters['search_completed_date_to'] != "") {
			if (isset($parameters['search_completed_date_from']) && $parameters['search_completed_date_from'] != "") {
				$query_issue_search  .= " AND i.issue_completed_date <= '".convertMDYtoYMD($parameters['search_completed_date_to'])."')";
			} else {
				$query_issue_search  .= " ".$search_control_type." i.issue_completed_date <= '".convertMDYtoYMD($parameters['search_completed_date_to'])."'";
			}
		}

		if ($search_control_type == "OR") {
			$query_issue_search .= ")";
		}
	}
//	echo "<p>Sorting by column: ".$order_by_column.", direction: ".$order_by_column_dir."</p>";
	if (isset($order_by_column) && $order_by_column != "") {
		$query_issue_search .= " ORDER BY ".$order_by_column;
		if (isset($order_by_dir) && $order_by_dir != "") {
			$query_issue_search .= " ".$order_by_column_dir;
		}
	} elseif (isset($parameters['search_results_as']) && $parameters['search_results_as'] == 'report') {
		// add default 'report' order here
	} else {
		// if no sort
		// $query_issue_search .= " ORDER BY i.issue_due_date ASC, i.issue_title ASC, staff ASC";
		//$order_by_column = "issue_due_date";
		$order_by_column = "sort_date_diff";
		$order_by_dir = "ASC";
		$query_issue_search .= " ORDER BY ".$order_by_column;
		$query_issue_search .= " ".$order_by_column_dir;
	}
/*
	if ((($advanced_search 
		&& isset($parameters['search_results_as']) && $parameters['search_results_as'] == 'table'
		&& isset($parameters['display_search']) && $parameters['display_search'] == '1')
		|| !$advanced_search) && isset($offset) && isset($rowsPerPage)) {
		$query_issue_search_limit  = " LIMIT ".$offset.", ".$rowsPerPage;
	}
*/	
	$query_issue_search_limit  = ""; // just put everything on one page...
	$result = mysql_query($query_issue_search.$query_issue_search_limit) or die('Error, query failed - '.mysql_error());
//	echo "<p>Testing, please ignore...</p>";
//	echo "<p>".$query_issue_search.$query_issue_search_limit."</p>";
?>