<?php
	$script_dir = realpath(dirname($_SERVER['SCRIPT_FILENAME']));
?>
<p><strong><?php echo $err_msg ?></strong></p>

<p>The configuration file for the current project is set to <tt><?php echo 
$cfg->configfile ?></tt> but this file cannot be opened. It should be in the 
directory <tt><?php echo $script_dir ?></tt>. You will need to restore this 
file to the correct location, correct the configuration file setting in the 
project administration, or create a new file.</p>