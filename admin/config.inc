<?
function stripslashes_recursive($value) {
	if (is_array($value)) {
		foreach ($value as $index => $val) {
				$value[$index] = stripslashes_recursive($val);
		}
		return $value;
	} else {
			return stripslashes($value);
	}
}


/* Use this if you do NOT want addslashes() to be run on all incoming data */

$_GET = stripslashes_recursive($_GET);
$_POST = stripslashes_recursive($_POST);
$_COOKIE = stripslashes_recursive($_COOKIE);
$_REQUEST = stripslashes_recursive($_REQUEST);
if (isset($form_r)) $form_r = stripslashes_recursive($form_r);
if (isset($form)) $form = stripslashes_recursive($form);


$mystring = $_SERVER['PHP_SELF'];
$findme	= "/";
$pos = strpos($mystring, $findme, 1);
$pos++;
$level_2 = substr($mystring, $pos);
$level_3 = strpos($level_2, $findme, 1);
$nav_color_switch = substr($level_2, 0, $level_3);

$mystring = $_SERVER['PHP_SELF'];
$findme	= '/';
$pos = strpos($mystring, $findme, 1);
$pos++;
$level_2 = substr($mystring, $pos); 
$level_3 = strpos($level_2, $findme, 1);
$level_3++;
$level_4 = substr($level_2, $level_3);
$level_5 = strpos($level_4, $findme, 1);
$nav_switch_admin = substr($level_4, 0, $level_5);

$_CFG = array();

$_CFG['debug'] = false;

/*---------------------------------------------------------------------------------------------------------------------------------------------
			DATABASE SETTINGS */

			$_CFG['dbType']						=	 "mysql";					 // view the abstraction layer for more possibilities
			$_CFG['dbHost']						=	 "localhost";
			$_CFG['dbUser']						=	 "*****";
			$_CFG['dbPass']						=	 "*****";
			$_CFG['dbName']						=	 "*****";
			$_CFG['dbPort']						=	 "";

/*---------------------------------------------------------------------------------------------------------------------------------------------
			HOST SETTINGS */
		
		$_CFG['host'] = $_SERVER['HTTP_HOST'];
				
		if($_CFG['host'] == "track.texaspolicy.com") {
			$_CFG['hostname']					=	 "track.texaspolicy.com";		
			$_CFG['title']			 			=	 "Track Everything";
			$_CFG['lang']							=	 "EN";
			$_CFG['langSQL']					=	 "";
			$_CFG['rootDir']					=	 "/home/tppf/track.texaspolicy.com/";
			$_CFG['rootDirAdmin']			=	 "/home/tppf/track.texaspolicy.com/admin/";
		}
		
/*---------------------------------------------------------------------------------------------------------------------------------------------
			GENERAL SETTINGS */

				$_CFG['maxFileSize']		=	 40000000;	// max upload is currently 40MB

				$_CFG['siteTitle']			=  "Track Everything";
				$_CFG['rootWeb']				=	 "/";
				$_CFG['rootWebAdmin']		=	 "/admin/";
				$_CFG['connType']				=	 (isset($HTTP_SERVER_VARS["HTTPS"]) && $HTTP_SERVER_VARS["HTTPS"]=="on") ? "https" : "http";
				$_CFG['rootURL']				=	 $_CFG['connType']."://".$_CFG['hostname'].$_CFG['rootWeb'];
				$_CFG['rootURLAdmin']		=	 $_CFG['connType']."://".$_CFG['hostname'].$_CFG['rootWebAdmin'];
//				$_CFG['jsDir']					=	 $_CFG['rootDir']."js/";
//				$_CFG['jsWeb']					=	 $_CFG['rootURL']."js/";
				$_CFG['jsWebAdmin']			=	 $_CFG['rootURLAdmin']."javascript/";
				$_CFG['jsDirAdmin']			=	 $_CFG['rootDirAdmin']."javascript/";
//				$_CFG['cssDir']					=	 $_CFG['rootDir']."css/";
//				$_CFG['cssWeb']					=	 $_CFG['rootURL']."css/";
				$_CFG['cssWebAdmin']		=	 $_CFG['rootURLAdmin']."css/";
				$_CFG['cssDirAdmin']		=	 $_CFG['rootDirAdmin']."css/";
//				$_CFG['admgmtDir']		 	=	 $_CFG['rootDir']."admgmt/";
//				$_CFG['admgmtWeb']			=	 $_CFG['rootURL']."admgmt/";
//				$_CFG['imgDir']					=	 $_CFG['rootDir']."images/";
				$_CFG['imgWeb']					=	 $_CFG['rootURL']."images/";
//				$_CFG['imgWebNav']			=	 $_CFG['rootURL']."images/nav/";
//				$_CFG['pgBG']					=	 $_CFG['imgWeb']."bg".$_CFG['langSQL'].".png";
//				$_CFG['pgLogo']				=	 $_CFG['imgWebNav']."ed".$_CFG['langSQL'].".png";
				$_CFG['imgDirAdmin']		=	 $_CFG['rootDirAdmin']."images/";
				$_CFG['imgWebAdmin']		=	 $_CFG['rootURLAdmin']."images/";
				$_CFG['filesDirAdmin']		=	 $_CFG['rootDirAdmin']."files/";
				$_CFG['filesWebAdmin']		=	 $_CFG['rootURLAdmin']."files/";
				$_CFG['uploadDirAdmin']		=	 $_CFG['filesDirAdmin']."upload/";
				$_CFG['uploadWebAdmin']		=	 $_CFG['filesWebAdmin']."upload/";
//				$_CFG['functionWeb']		=	 $_CFG['rootURL']."functions/";
//				$_CFG['functionDir']		=	 $_CFG['rootDir']."functions/";
//				$_CFG['fpdfWeb']				=	 $_CFG['rootURL']."fpdf/";
//				$_CFG['fpdfDir']			 	=	 $_CFG['rootDir']."fpdf/";
				$_CFG['functionWebAdmin']	=	 $_CFG['rootURLAdmin']."functions/";
				$_CFG['functionDirAdmin']	=	 $_CFG['rootDirAdmin']."functions/";
//				$_CFG['navDir']					=	 $_CFG['rootDir']."nav/";
//				$_CFG['navWeb']			 	 	=	 $_CFG['rootDir']."nav/";
//				$_CFG['navDirProg']			=	 $_CFG['rootDir']."program/nav/";
				$_CFG['navDirAdmin']		=	 $_CFG['rootDirAdmin']."nav/";
				$_CFG['navWebAdmin']		=	 $_CFG['rootDirAdmin']."nav/";
//				$_CFG['flashDir']				=	 $_CFG['rootDir']."flash/";
//				$_CFG['flashWeb']				=	 $_CFG['rootURL']."flash/";
//				$_CFG['adtrackDir']			=	 $_CFG['rootDir']."adtrack/";
//				$_CFG['adtrackWeb']			=	 $_CFG['rootURL']."adtrack/";
//				$_CFG['flashDirProg']		=	 $_CFG['rootDir']."program/flash/";
//				$_CFG['imgPhotos']			=	 $_CFG['rootURL']."photos/";
//				$_CFG['imgThumbs']			=	 $_CFG['rootURL']."thumbs/";
//				$_CFG['siteImgDir']			=	 $_CFG['imgDir']."/";
//				$_CFG['siteImgWeb']			=	 $_CFG['imgWeb']."/";
//				$_CFG['sitePhotosWeb']	=	 $_CFG['imgPhotos']."/";
//				$_CFG['siteThumbsWeb']	=	 $_CFG['imgThumbs']."/";
//				$_CFG['cfgDir']					=	 $_CFG['rootDir']."/_config";
//				$_CFG['cfgWeb']					=	 $_CFG['rootURL']."/_config";
//				$_CFG['tplDir']					=	 $_CFG['rootDir']."/_templates";
//				$_CFG['tplWeb']					=	 $_CFG['rootURL']."/_templates";
//				$_CFG['incDir']					=	 $_CFG['rootDir']."/_inc";
//				$_CFG['incWeb']					=	 $_CFG['rootWeb']."/_inc"; 
				

/*---------------------------------------------------------------------------------------------------------------------------------------------
			META SETTINGS */


				$_CFG['metaDesc']				=	 "";
				$_CFG['metaKey']				=	 "";
				
				
/*---------------------------------------------------------------------------------------------------------------------------------------------
			LANGUAGE SETTINGS */
		
//				session_start();
				$_CFG['lang']						=	 'EN';
				$_CFG['langSQL']				=	 "";
				
				include("lang.inc");

/*---------------------------------------------------------------------------------------------------------------------------------------------
			USER SETTINGS */

				$_CFG['userType']				=	 array();
				$_CFG['userType'][0]		=	 $_CFG['langDisabled'];
				$_CFG['userType'][1]		=	 $_CFG['langAdmin'];
				$_CFG['userType'][2]		=	 $_CFG['langEditor'];
				$_CFG['userType'][3]		=	 $_CFG['langContributor'];
				$_CFG['userType'][4]		=	 $_CFG['langUser'];

/*---------------------------------------------------------------------------------------------------------------------------------------------
			DEFINITIONS */

				// cat_id for the Policy/Research unit
				$unit_policy_research = 178;
				define('ISSUE_UNIT_POLICY_RESEARCH', 178);
				
				// cat_id for the Research/Write activity
				$unit_activity_research_write = 186;
				define('ISSUE_ACTIVITY_RESEARCH_WRITE', 186);
				
				// cat_id for the Legislative Contacts type
				$type_contact = 145;
				define('ISSUE_TYPE_CONTACT', 145);
				
				// cat_id for the Publications type
				$type_publication = 168;
				define('ISSUE_TYPE_PUBLICATION', 168);
				
				// cat_id for the Completed status
				$status_completed = 140;
				define('ISSUE_STATUS_COMPLETED', 140);
				
				// cat_id for the Not Started status
				$status_not_started = 134;
				define('ISSUE_STATUS_NOT_STARTED', 134);
				
				// cat_id for the Late status
				$status_late = 141;
				define('ISSUE_STATUS_LATE', 141);

?>
