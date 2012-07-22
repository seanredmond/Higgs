<div class="span8 offset1">
	<h1>Project Settings</h1>
	
	<form class="form-horizontal well" method="post" action='./'>
	<?php echo form_fields($syscfg, 'project') ?>
		<div class="form-actions">
			<button type="submit" class="btn btn-primary">
				Save changes
			</button>
			<button class="btn">Cancel</button>
		</div>
	</form>
</div>