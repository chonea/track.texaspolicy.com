<?
if (!function_exists('getDaysOut')) {
	function getDaysOut($datetime,$datenow='') {
		if ($datenow == '') {
			// $datenow = time();
			$datenow = date(time());
		} else {
			$datenowArr = explode(" ",$datenow);
			if (!isset($datenowArr[1])) {
				$datenowArr[1] = "00:00:00";
			}
			$datenowArr = explode("/",$datenowArr[0]);
			$timenowArr = explode(":",$datenowArr[1]);
			$datenow = mktime($timenowArr[0],$timenowArr[1],0,$datenowArr[0],$datenowArr[1],$datenowArr[2]);
		}
		$datetimeArr = explode(" ",$datetime);
		if (!isset($datetimeArr[1])) {
			$datetimeArr[1] = "00:00:00";
		}
		$dateArr = explode("/",$datetimeArr[0]);
		$timeArr = explode(":",$datetimeArr[1]);
		$datedue = mktime($timeArr[0],$timeArr[1],0,$dateArr[0],$dateArr[1],$dateArr[2]);

//		$daysout = $datedue/86400 - $datenow/86400;	// 86400 seconds per day
		$daysout = ($datedue + 86400)/86400 - $datenow/86400;	// 86400 seconds per day (add 1 extra day so past due tomorrow)
		return $daysout;
	}
}

if (!function_exists('convertMDYtoYMD')) {
	function convertMDYtoYMD($datetime) {
		
		$datetimeArr = explode(" ",$datetime);
		if (!isset($datetimeArr[1])) {
			$datetimeArr[1] = "00:00:00";
		}
		$dateArr = explode("/",$datetimeArr[0]);
		$timeArr = explode(":",$datetimeArr[1]);
		$dateStr = '';
		if (isset($dateArr[2])) $dateStr .= $dateArr[2]."-";
		if (isset($dateArr[0])) $dateStr .= $dateArr[0]."-";
		if (isset($dateArr[1])) $dateStr .= $dateArr[1]." ";
		if (isset($timeArr[0])) $dateStr .= $timeArr[0].":";
		if (isset($timeArr[1])) $dateStr .= $timeArr[1].":";
		if (isset($timeArr[2])) $dateStr .= $timeArr[2];
		return $dateStr;
		
		//return date("Y-m-d H:i:s",$datetime);
	}
}

if (!function_exists('is_odd')) {
	//IS ODD Function
	function is_odd($number) {
	   return $number & 1; // 0 = even, 1 = odd
	}
}

if (!function_exists('booleanYesNo')) {
	function booleanYesNo($value) {
		if ($value == 0)
			return "No";
		else
			return "Yes";
	}
}

if (!function_exists('getCookie')) {
	function getCookie($cookiename) {	
		if (isset($_COOKIE[$cookiename])) {
			$cookiearray = array();
			$temp_cookie_array = explode('&',$_COOKIE[$cookiename]);
			foreach ($temp_cookie_array as $temp_parameter) {
				$temp_parameter_pair = explode('=',$temp_parameter);
				if ($temp_parameter_pair[0] <> '') {
					if (substr($temp_parameter_pair[1],0,5) != "array") {
						$cookiearray[($temp_parameter_pair[0])] = $temp_parameter_pair[1];
					} else {
						$temp_values = substr($temp_parameter_pair[1],6,strlen($temp_parameter_pair[1])-7);
						$cookiearray[($temp_parameter_pair[0])] = explode(",",$temp_values);
						foreach ($cookiearray[($temp_parameter_pair[0])] as $value) {
							if ($value == 1) $nav[($temp_parameter_pair[0])][] = true;
							else $cookiearray[($temp_parameter_pair[0])][] = false;
						}
					}
				}
			}
			return $cookiearray;
		}
	}
}

if (!function_exists('deleteCookie')) {
	function deleteCookie($cookiename) {
		if ($cookiename) {
			// if the cookie exists, delete it
			if (isset($_COOKIE[$cookiename])) {
				// the cookie array is null
				$_COOKIE[$cookiename] = '';
				// update the cookie with an expiration date in the past
				setcookie($cookiename, "", time() - (1 * 24 * 60 * 60));
			}
		}
	}
}

if (!function_exists('createCookie')) {
	function createCookie($cookiename='', $cookievalue='') {
		if ($cookiename && $cookievalue) {
			// remove previous cookie
			deleteCookie($cookiename);
			// now create the cookie (expires in 1 day)
			setcookie($cookiename, $cookievalue, time() + (1 * 24 * 60 * 60));
		}
	}
}

// not in use
function updateView($view = '', $subview = '') {
	if (isset($_REQUEST['view']) && !empty($_REQUEST['view'])) {
		$_SESSION['view'] = $_REQUEST['view'];
		if (isset($_REQUEST['subview']) && !empty($_REQUEST['subview'])) {
			$_SESSION['subview'] = $_REQUEST['subview'];
		} else {
			$_SESSION['subview'] = '';
			$_REQUEST['subview'] = '';
		}
	} elseif (!isset($_REQUEST['view']) && !empty($_SESSION['view'])) {
		$_REQUEST['view'] = $_SESSION['view'];
		if (!isset($_REQUEST['subview']) && !empty($_SESSION['subview'])) {
			$_REQUEST['subview'] = $_SESSION['subview'];
		} else {
			$_SESSION['subview'] = '';
			$_REQUEST['subview'] = '';
		}
	} else {
		$_SESSION['view'] = '';
		$_REQUEST['view'] = '';
	}
}

// not in use
function updateFilter() {
	if (isset($_REQUEST['filter'][$_SESSION['view']]) && !empty($_REQUEST['filter'][$_SESSION['view']])) {
		$_SESSION['filter'][$_SESSION['view']] = $_REQUEST['filter'][$_SESSION['view']];
	} elseif (!isset($_REQUEST['filter'][$_SESSION['view']]) && !empty($_SESSION['filter'][$_SESSION['view']])) {
		$_REQUEST['filter'][$_SESSION['view']] = $_SESSION['filter'][$_SESSION['view']];
	} else {
		$_SESSION['filter'][$_SESSION['view']] = '';
		$_REQUEST['filter'][$_SESSION['view']] = '';
	}
}

?>