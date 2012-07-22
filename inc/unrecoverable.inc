<div class="span8 offset1 hero-unit">
	<h1>Big Problem</h1>
	<p>An error has occurred that we can't recover from. The error message 
		is:</p>
	<blockquote class="errmsg">
		<p> <?php echo $LASTERR->getMessage() ?>.</p> 
	</blockquote>
	
	<p>Here is the stack trace, in case it's helpful:</p>
	<table class="table table-bordered table-striped table-condensed">
		<thead>
			<tr>
				<th>File</th>
				<th>Line</th>
				<th>In function</th>
			</tr>
		</thead>				
		<tbody>
		<?php foreach($LASTERR->getTrace() as $trace) { ?>
			<tr>
				<td><?php print_r($trace['file']) ?></td>
				<td><?php print_r($trace['line']) ?></td>
				<td><?php print_r($trace['function']) ?></td>
			</tr>
		<?php } ?>
		</tbody>
	</table>
		
</div>