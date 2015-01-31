<?php
$host="a";
$user="jfrancom";
$password="francom1";
$databasename="comments";

$con=mysqli_connect($host, $user, $password) or die ("access denied");
$mysqli_select_db($databasename);

$result=mysqli_query("select * from $databasename");

echo mysqli_error($con);

?>