<?php

//print_r($_POST);
$firstname=$_POST['firstname'];
$lastname=$_POST['lastname'];
$phone=$_POST['phone'];
$url=$_POST['url'];


if($firstname=='' || $lastname=='')
{
	echo "nothing entered";
}

if (!filter_var($url, filter_validate_url))
{
	echo "Invalid url";
}
if(!preg_match("/^([0-9]{3}-)?[0-9]{3}-[0-9]{4}$/", $phone))
{
	echo "<h1>INvalid phone</h1>";
}

?>