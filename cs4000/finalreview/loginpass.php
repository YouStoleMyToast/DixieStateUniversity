<?php

$uname=$-POST['username'];
$pwd=$_POST['password'];
if($uname=='joe' && pwd=='francom')
{
	echo 'valid';
}
else
{
	echo 'wrong';
}

?>