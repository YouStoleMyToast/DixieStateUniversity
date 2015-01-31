<?php

include_once('a_functions.php');

$name=$_GET['row'];
$action=$_GET['action'];

echo $name.$action;

if($action='del')
{
	$sql="Delete from comments where name='$name'";
	$results=doquery($sql);
	//if(mysqli_affected_rows)
	header("location: ./comments.php');
}

?>