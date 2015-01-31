<!DOCTYPE html>

<html>
<head>
</head>
<body>


<?php
echo "<form method='get'>";
	echo "<input type='text' />";
	echo "<input type='submit' name='send' value=Submit' />";

if(isset($_GET['send']))
{
	$name='midterm';
	$send=$_GET['send'];
	$time=time()+86400;
	setcookie($name, $send, $time);
	
}
if(isset($_COOKIE['midterm']))
{
	echo "<table border=1>";
	echo "<tr>";
	echo "<td>".$send."</td>";
	echo "<tr>";
	echo "</table>";
}

echo "</form>";

echo "<div id='main'>";


echo "</div>";




?>
</body>
