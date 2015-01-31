<?php
function queryfunc($query)
{
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
    $result = mysqli_query($connect, $query) or die("can't do query " . $query . mysqli_error($connect));
	return $result;
}
?>
