<?php
function queryfunction($query)
{
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann");// or die("can't connect");
    $result = mysqli_query($connect, $query);// or die("can't do query " . $query . mysqli_error($connect));
	return $result;
}

function memberdropdown()
{
	$query="select username from oipmembers";
	$results=queryfunction($query);
	echo "<select>";
	while ($row=mysqli_fetch_array($results))
	{
		echo "<option>".$row[0]."</option>";
	}
	echo "</select>";
}


?>






