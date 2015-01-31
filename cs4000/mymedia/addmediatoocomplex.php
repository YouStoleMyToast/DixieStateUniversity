<?php
include_once "header.php";

?>

<h1><title>Add Media</title></h1>

<form method="POST" action="addmedia.php">
	<label for="title">Title</label>
	<input type="text" name="title" />
	<label for="media_type">Media Type</label>
	<input type="text" name="media_type" />
	<label for="description">Description</label>
	<input name="description">	
	<p>	
	<label for="rating_id">Rating</label>
	<input type="text" name="rating_id" />
	<label for="stuff">Additional Stuff</label>
	<input type="text" name="stuff" />
	<label for="link">Links</label>
	<input type="text" name="link" />
	<label for="year">Year</label>
	<input type="text" name="year" />
	
	<p><input type="submit" name="btn_submit" value="Submit"/></p>
</form>



<?php
if (isset($_POST)) 
{
    $media_title = $_POST["title"];
    $media_type = $_POST["media_type"];
    $media_description = $_POST["description"];
	$media_rating = $_POST["rating_id"];
	$media_stuff = $_POST["stuff"];
	$media_link = $_POST["link"];
	$media_year = $_POST["year"];
    $query = "INSERT into items VALUES(NULL, '$media_title', '$media_description', '$media_type','$media_rating','$media_stuff','$media_link','$media_year',1)";
	if ($media_title!="")
	{
		queryfunc($query);
	}
}
if(isset($_GET['deleteaction']))
{
	switch($_GET['deleteaction'])
	{	
		case "delete":
			$query="delete from items where item_id='".$_GET[item_id]."'";
			queryfunc($query);
	}
}	
//editaction=edit&item_id=$row[item_id]\	
if(isset($_GET['editaction']))
{
	echo "<form method='POST' action='addmedia.php'>";
	switch($_GET['editaction'])
	{	
		case "edittitle":
			$col="title";
			break;
		case "edittype":
			$col="media_type";
			break;
		case "editdescription":
			$col="description";
			break;
		case "editrating":
			$col="media_rating";
			break;
		case "editstuff":
			$col="stuff";
			break;
		case "editlink":
			$col="media_link";
			break;
		case "edityear":
			$col="media_year";
			break;
	}
	echo "<label for='editdata'>$col</label>";
	echo "<input type='text' name='editdata'/>";
	echo "<input type='submit' name='btn_submit' value='Edit'/>";
	echo "</form>";
	$query="update items set $col='".$_POST[editdata]."' where item_id='".$_GET[item_id]."'";
	echo $query;
	queryfunc($query);
}
if(!isset($_GET['editaction'],$col))
{
	$col="No Edit Type Selected ";
	echo "<form method='POST' action='addmedia.php'>";
	echo "<label>$col</label>";
	echo "<input type='submit' name='btn_submit' value='Edit'/>";
	echo "</form>";
}

echo "<h2>Music</h2>";
echo "<table>";
echo "<tr>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">MID</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=edittitle\">Title</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=edittype\">Media Type</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=editdescription\">Description</a></td>";
echo "<p>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=editrating\">Rating</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=editstuff\">Stuff</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=editlink\">Link</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;color:blue;\" href=\"./addmedia.php?editaction=edityear\">Year</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">UID</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">Delete</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">Edit</a></td>";
echo "</tr>";

$query="select * from items";
$results=queryfunc($query);
while ($row=mysqli_fetch_array($results))//mysqli_fetch_assoc while i can fetch a row out of the results with using column name in [] below//if fetch array you can use index numbers in [] below
{
	echo "<tr>";
	echo "<td> $row[item_id]</td>";
	echo "<td> $row[title]</td>";
	echo "<td> $row[media_type]</td>";
	echo "<td> $row[description]</td>";
	echo "<td> $row[rating_id]</td>";
	echo "<td> $row[stuff]</td>";
	echo "<td> $row[link]</td>";
	echo "<td> $row[year]</td>";
	echo "<td> $row[user_id]</td>";
	echo "<td> <a style=\"color:blue;font-size:15px;font-family:ariel;\" href=\"./addmedia.php?deleteaction=delete&item_id=$row[item_id]\">Delete</a></td>";
	echo "<td> <a style=\"color:blue;font-size:15px;font-family:ariel;\" href=\"./addmedia.php?editrow=edit&item_id=$row[item_id]\">Row</a></td>";
	echo "</tr>";
}

include_once "footer.php";
?>