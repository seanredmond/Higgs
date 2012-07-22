<?php
function handleError($errno, $errstr, $errfile, $errline, array $errcontext) {
	// error was suppressed with the @-operator
	if (0 === error_reporting()) {
		return false;
	}

	throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
}
set_error_handler('handleError');

function to_object($array) {
  $obj = new stdClass;
  foreach($array as $k => $v) {
     if(is_array($v)) {
        $obj->{$k} = to_object($v); //RECURSION
     } else {
        $obj->{$k} = $v;
     }
  }
  return $obj;
}
function check_route() {
	$stat = H_STAT_UNKNOWN;
	$err = null;
	// print_r($_SERVER);
	$route = array_slice(explode('/', $_SERVER['QUERY_STRING']), 1);
	// print_r($route);
	
	if (count($route) > 0) {
		if ($route[0] == 'start-new-project') {
			try {
				$stat = new_master_settings();
			} catch(HiggsError $e) {
				$stat = (H_STAT_UNRECOVERABLE);
				$err = $e;
			}
		} elseif ($route[0] == 'no-thanks') {
			$stat = H_STAT_NOTHANKS;
		}
	}
	return array($stat, $err);
}

function get_contents_or_complain($fn) {
	try {
		return file_get_contents($fn);		
	} catch(Exception $e) {
		$msg = $e->getMessage();
		
		if (preg_match('/permission denied/i', $msg)) {
			throw new HiggsFilePermissionsError("Could not open file $fn: Permission denied");
		}
		
		if (preg_match('/no such file/i', $msg)) {
			throw new HiggsFileNotFoundError(
				"Could not open file $fn: File not found");
		}
		throw $e;
	}
}

function put_contents_or_complain($fn, $data) {
	try {
		return file_put_contents($fn, $data);		
	} catch(Exception $e) {
		$msg = $e->getMessage();	
		if (preg_match('/permission denied/i', $msg)) {
			throw new HiggsFilePermissionsError("Could not write to file $fn: Permission denied");
		}
		throw $e;
	}
}

function new_master_settings() {
	$dist = H_FILES_MASTER_DIST;
	$cfg =  H_FILES_MASTER;
	$data = get_contents_or_complain($dist);
	$stat = put_contents_or_complain($cfg, $data);		

	if ($stat !== FALSE) {
		header( 'Location: ./' );
	}
	return H_STAT_UNKNOWN;
}

function get_sysconfig() {
	$file = get_contents_or_complain(H_FILES_MASTER);
	$cfg = json_decode($file);
	if ($cfg === NULL) {
		throw new HiggsJsonDecodeError("Failed to decode JSON in ".
			H_FILES_MASTER);
	}
	
	
	return $cfg;
}

function form_fields($json, $section) {
	$html = '';
	foreach ($json->properties->project as $key => $val) {
		$html .= one_field($section, $key, $val, $json->$section->$key);
	}
	return $html;
}

function one_field($section, $name, $data, $val) {
	$id = $section . '-' . $name;
	$field_name = "{$section}[{$name}]";
	$html = <<<HTML
<fieldset>
	<div class="control-group">
		<label class="control-label" for="$id">{$data->label}</label>
		<div class="controls">
			<input type="text" class="input-xlarge" id="{$id}" 
				name="{$field_name}" placeholder="{$data->placeholder}" 
				value="{$val}">
			<p class="help-block">{$data->description}</p>
		</div>
	</div>
</fieldset>
HTML;

	return $html;
}


function formRow($prop, $val, $proj) {
	if (isset($proj->$prop)) {
		$cur_val = $proj->$prop;
	} else {
		$cur_val = null;
	}

	if (isset($val->placeholder)) {
		$placeholder = $val->placeholder;
	} else {
		$placeholder = null;
	}
		
	if ($val->type == 'string') {
		return <<<HTML
 <fieldset>
   <div class="control-group">
     <label class="control-label" for="input01">{$val->label}</label>
     <div class="controls">
       <input type="text" class="input-xlarge" id="input01" value="{$cur_val}" placeholder="$placeholder" name="prop[a][$prop]">
			<!-- button class="btn btn-danger btn-mini">Remove</button -->
       <p class="help-block">{$val->description}</p>
     </div>
   </div>
 </fieldset>
HTML;
	}
}

class HiggsError extends Exception {};
class HiggsFileNotFoundError extends HiggsError {};
class HiggsFilePermissionsError extends HiggsError {};
class HiggsJsonDecodeError extends HiggsError {};

?>

