<?php

//note firefox has a way to format json called "json view"
$zip=$_POST['zip'];
$zip='84780';
$key="your key here"

$url="http://api.wunderground.com/api/Your_Key/conditions/q/CA/San_Francisco.json"
//echo $url;//for checking to make sure it is displaying the correct output

$json_string=file_get_contents($url);
$parsed_json=json_decode($json_string, true);
//echo $parsed_json->('current_observation')->{'temperature_string'};//without true in above
echo 'The temp is'.$parsed_json['current_observation']['temperature_string'];//with true in above

?>