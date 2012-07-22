<?php
	ini_set('display_errors', true);
	ini_set('display_startup_errors', true);
	error_reporting(E_ALL);
	include 'inc/constants.inc';
	include 'inc/functions.inc';

	$STATUS = H_STAT_UNKNOWN;
	$LASTERR = null;
	$snippet = 'unknown.inc';
	

	try {
		list($STATUS, $LASTERR) = check_route();


		if ($STATUS === H_STAT_UNKNOWN) {
			try {
				$syscfg = get_sysconfig();
				if (!isset($syscfg->project->name)) {
					$STATUS = H_STAT_EMPTYPROJECT;
				}
				// print_r($syscfg);
			} catch (HiggsFileNotFoundError $e) {
				$STATUS = H_STAT_NEWPROJECT;
			}
		}

		if ($_SERVER['REQUEST_METHOD'] == 'POST') {
			$syscfg = to_object(array_merge((array) $syscfg, $_POST));
			put_contents_or_complain(H_FILES_MASTER, json_encode($syscfg));
		}


		if ($STATUS === H_STAT_NEWPROJECT) {
			$snippet = 'start_new_project.inc';
		} elseif ($STATUS === H_STAT_NOTHANKS) {
			$snippet = 'no_thanks.inc';
		} elseif ($STATUS === H_STAT_UNRECOVERABLE) {
			$snippet = "unrecoverable.inc";
		} elseif ($STATUS === H_STAT_EMPTYPROJECT) {
			$snippet = 'project_settings.inc';
		}
	} catch(HiggsError $e) {
		$STATUS = H_STAT_UNRECOVERABLE;
		$LASTERR = $e;
		$snippet = "unrecoverable.inc";
	}

?>

<!doctype html>
<html class="no-js" lang="en">
<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">

	<title></title>
	<meta name="description" content="">
	<meta name="author" content="">

	<meta name="viewport" content="width=device-width">

	<link rel="stylesheet/less" href="less/style.less">
	<script src="js/libs/less-1.3.0.min.js"></script>
	
	<!-- Use SimpLESS (Win/Linux/Mac) or LESS.app (Mac) to compile your .less files
	to style.css, and replace the 2 lines above by this one:

	<link rel="stylesheet" href="less/style.css">
	 -->

	<script src="js/libs/modernizr-2.5.3.min.js"></script>
</head>
<body>
	<?php include 'inc/navbar.php' ?>
	
	<div class="container">
		<div class="row">
		<?php include "inc/{$snippet}" ?>
		</div>
		<hr/>
		<footer>
			<p>&copy; Company 2012</p>
		</footer>
	</div>
	<script src="//ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js"></script>
	<script>window.jQuery || document.write('<script src="js/libs/jquery-1.7.2.min.js"><\/script>')</script>

	<script src="js/libs/bootstrap/bootstrap.min.js"></script>

	<script src="js/script.js"></script>
</body>
</html>
