<?
//////////////////////////Format Functions/////////////////
//////////////////////////////////////////////////////////
function valid_email ($email) {
if (eregi("^[0-9a-z]([-_.]?[0-9a-z])*@[0-9a-z]([-.]?[0-9a-z])*\\.[a-z]{2,3}$", $email, $check)) {
return TRUE;}
return FALSE;}

//////////////////////////Login/Session Functions//////////
//////////////////////////////////////////////////////////


function loginadmin($sid){
	global $sid, $key_id, $screen_name, $admin_level, $_CFG;
	if (isset($sid) && !empty($sid)){
		include('data_connect.inc');
		$qry = "SELECT *
			FROM admin_sessions, admin_passports
			WHERE admin_sessions.profile_id = admin_passports.id AND admin_sessions.sesskey = '$sid'
			";
	
		$qid = mysql_query($qry, $db) or die(mysql_error());
		
		if (mysql_num_rows($qid) == 1){
			$row=mysql_fetch_array($qid);
			$key_id = $row[id];
			$screen_name = $row[user_name];
			$admin_level = $row[administrator];	
		
			//Refresh Session Time
			$expiry = time() + 1800;
			$time = time();
		
			$qry_reset = "UPDATE admin_sessions
				SET expiry = '$expiry'
				WHERE sesskey = '$sid' AND expiry > '$time'
				";
		
			$qid2 = mysql_query($qry_reset, $db) or die(mysql_error());
		
			if (! $qid2){
				Header ("Location: session_expired.php");
			}
		}			
		elseif(mysql_num_rows($qid) != 1){
			Header ('Location:  '.$_CFG['rootURLAdmin'].'login/');
		}
		mysql_close($db);
	}
	else {
		Header ('Location:  '.$_CFG['rootURLAdmin'].'login/');
	}
}

function sess_gc() {
	global $expiry;
	include('data_connect.inc');
	$expiry = time() - 800;
	$qry = "DELETE FROM admin_sessions WHERE expiry < ".$expiry;
	mysql_query($qry) or die(mysql_error());
	//mysql_close($db);
}

//////////////////////STRING FUNCTION
function strrposmixed($haystack, $needle, $start=0) {
	global $lastFoundPos;
   // init start as the end of the str if not set
   if($start == 0) {
       $start = strlen($haystack);
   }
  
   // searches backward from $start
   $currentStrPos=$start;
   $lastFoundPos=false;
  
   while($currentStrPos != 0) {
       if(!(strpos($haystack,$needle,$currentStrPos) === false)) {
           $lastFoundPos=strpos($haystack,$needle,$currentStrPos);
           break;
       }
       $currentStrPos--;
   }
  
   if($lastFoundPos === false) {
       return false;
   } else {
       return $lastFoundPos;
   }
}



// Allows for strpos with case insensitvity to the haystack or needle. 
function stripos($haystack, $needle, $i = 0){
    return strpos($haystack, stristr( $haystack, $needle ), $i);
}

// Get Help Array
function getHelpArray($pagename, $db){
	$help_query = "SELECT *	FROM admin_help_new	WHERE pagename = '".$pagename."'";
	$help_result = mysql_query($help_query, $db) or die (mysql_error()." - ".$help_query);
	$return_array = array();
	while ($help_info = mysql_fetch_array($help_result)){
		$return_array[$help_info['field_name']] = array('Field Name' => $help_info['field_name'], 'Friendly Name' => $help_info['friendly_name'], 'Value' => $help_info['field_value']);
	}
	return $return_array;
}

// Display Help Block
function showHelpBlock($help_array, $help_field){
	if (array_key_exists($help_field, $help_array)){
		echo "&nbsp;&nbsp;<img src=\"../images/help.gif\" border=\"0\" onMouseOut=\"HideHelp('".$help_field."')\" onmouseover=\"ShowHelp('".$help_field."', '".$help_array[$help_field]['Friendly Name']."', '".$help_array[$help_field]['Value']."','".$_SESSION['administrator']."')\"><div style=\"\" id=\"".$help_field."\" name=\"".$help_field."\"></div>";
	}	
}

//Alternate of using getimagesize for finding out if an image exists as file_exists was failing always.
function url_exists($url) {
	if(file_get_contents($url,0,NULL,0,1)){
		return 1;
	}
	else { 
		return 0;
	}
}


//***********************************************************
//
// Begin run_query function
//

function run_query($query, $db = ''){
	if ($db != ''){
		$result = mysql_query($query, $db) or die(mysql_error()." - ".$query);
	}
	else {		
		$result = mysql_query($query) or die(mysql_error()." - ".$query);
	}
	return $result;
}

/*
function updateNextMemberId() {
	// don't use this
	$id_query = mysql_query("SELECT * FROM memid WHERE id=1");
	if ($id_row = mysql_fetch_array($id_query)) {
		$MemID = $id_row["memnum"] + 1;
		while ($mem_row = mysql_fetch_row(mysql_query("SELECT memid FROM members WHERE memid = '".$MemID."' ORDER BY memid DESC LIMIT 1"))) {
			$MemID = $MemID + 1;
		}
		$id_update = mysql_query("UPDATE memid SET memnum=$MemID WHERE id=1");
		$next_mem_id = $MemID;
	}
}
function getNextMemberId() {
	$id_query = mysql_query("SELECT memid FROM members ORDER BY memid DESC LIMIT 1");
	if ($id_row = mysql_fetch_array($id_query)) {
		$MemID = $id_row["memnum"] + 1;
		while ($mem_row = mysql_fetch_row(mysql_query("SELECT memid FROM members WHERE memid = '".$MemID."' ORDER BY memid DESC LIMIT 1"))) {
			$MemID = $mem_row['memid'] + 1;
		}
	}
	return $MemID;
}
if (!function_exists('getDaysOut')) {
	function getDaysOut($datetime) {
		$datenow = time();
		$datetimeArr = explode(" ",$datetime);
		if (!isset($datetimeArr[1])) {
			$datetimeArr[1] = "00:00:00";
		}
		$dateArr = explode("/",$datetimeArr[0]);
		$timeArr = explode(":",$datetimeArr[1]);
		$datedue = mktime($timeArr[0],$timeArr[1],0,$dateArr[0],$dateArr[1],$dateArr[2]);
		$daysout = $datedue/86400 - $datenow/86400;	// 86400 seconds per day
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
		return $dateArr[2]."-".$dateArr[0]."-".$dateArr[0]." ".$timeArr[0].":".$timeArr[1].":".$timeArr[2];
	}
}
*/
?>