<?php
	$script_dir = realpath(dirname($_SERVER['SCRIPT_FILENAME']));
?>
<p><strong><?php echo $err_msg ?></strong></p>

<p>There should be a file named <tt>project.json</tt> in the directory 
	<tt><?php echo $script_dir ?></tt>. This file has a particular format is is required to open or start a Higgs project. A blank <tt>project.json</tt> file can be found in the Higgs distribution.</p>