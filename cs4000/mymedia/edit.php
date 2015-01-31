<?php
include_once 'mediafunctions.php';

if (isset($_POST['title'])) 
{
    $editquery = "UPDATE `items` SET `title`='".$_POST['title']."', `description`='".$_POST['description']."', `media_type`='".$_POST['media_type']."', `rating_id`='".$_POST['rating_id']."',`stuff`='".$_POST['stuff']."',`link`='".$_POST['link']."', `year`='".$_POST['year']."' WHERE `item_id`=".$_POST['id'];
	if ($_POST['title']!="")
	{
		queryfunc($editquery);
	}
	header('Location: http://www.ebeilmann.php.cs.dixie.edu/CS%204000/mymedia/addmedia.php');
	die();
}
include_once 'header.php';

$query="SELECT * FROM items where item_id=".$_GET[item_id];
$results=queryfunc($query);
$result=mysqli_fetch_array($results);

echo "<h1><title>Edit Media</title></h1>";

echo "<form method='POST' action='".$_SERVER['PHP_SELF']."'>";
	echo "<label for='title'>Title</label>";
	echo '<input type="hidden" value="'.$result[0].'" name="id" />';
	echo "<input type='text' name='title' value='".$result[1]."' />";
	echo "<label for='description'>Description</label>";
	echo "<input name='description value='".$result[2]."' />";
	echo "<label for='media_type'>Media Type</label>";
	echo "<input type='text' name='media_type' value='".$result[3]."' />";
	echo "<p>";
	echo "<label for='rating_id'>Rating</label>";
	echo "<select name='rating_id' value='".$result[4]."' />";
		echo "<option>1</option>";
		echo "<option>2</option>";
		echo "<option>3</option>";
		echo "<option>4</option>";
		echo "<option>5</option>";
	echo "</select>";
	echo "<label for='stuff'>Additional Stuff</label>";
	echo "<input type='text' name='stuff' value='".$result[5]."' />";
	echo "<label for='link'>Links</label>";
	echo "<input type='text' name='link' value='".$result[6]."' />";
	echo "<label for='year'>Year</label>";
	echo "<input type='text' name='year' value='".$result[7]."' />";
	
	echo "<p><input type='submit' name='edit_submit' value='Update'/></p>";
echo "</form>";



include_once 'footer.php';
?>