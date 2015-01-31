<?php
include_once('function.php');

function doquerry($sql)
{
	$conn=mysqli_connect('mysqli.cs.dixie.edu','jfrancom','francom1','jfrancom');
	$results=mysqli_query($conn, $sql);
	mysqli_close($conn);
	return $result;
}

if(isset($_POST))
{
	$name=$_POST['user'];
	$comment=$_POST['myComment'];
	$sql="insert into comments (name,comments) values ('$name', '$comments')";
	$results=doquery($sql);
}
?>

<form action=='<?=$_SERVER['PHP_SELF']?>" method="POST">
	<input type="text" name="user" />
	<textarea name="myComment" ></textarea>
	<input type="submit" value='make a comment'name="submit" />
</form>

<?php
	$results=doquery("select * from comments");
	if(mysqli_num_rows($results)>0)
	{
		echo "<div idf ='results'>";
		while($row=mysqli_fetch_assoc($results))
		$name=$row['name'];
		{
			$edit = "<a href='./edit.php?row=$name&action=edit'>edit</a>";
			$del = "<a href='./edit.php?row=$name&action=del'</a>";
			echo "<p>$row[name]: $row[comment] $edit $del</p>";
		}
		echo "</div>";
	}
	else
	{
		echo 'no results';
	}
?>