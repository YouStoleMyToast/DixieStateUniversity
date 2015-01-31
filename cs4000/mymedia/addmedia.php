<?php
include_once "header.php";


echo "<h1><title>Add Media</title></h1>";

if(!isset($_REQUEST['editaction']))
{
	echo "<form method='POST' action='addmedia.php'>";
		echo "<label for='title'>Title</label>";
		echo "<input type='text' name='title' />";
		echo "<label for='description'>Description</label>";
		echo "<input type='text' name='description'>";
		echo "<label for='media_type'>Media Type</label>";
		echo "<input type='text' name='media_type'/>";
		echo "<p>";
		echo "<label for='rating_id'>Rating</label>";
		echo "<select name='rating_id'/>";
			echo "<option>1</option>";
			echo "<option>2</option>";
			echo "<option>3</option>";
			echo "<option>4</option>";
			echo "<option>5</option>";
		echo "</select>";
		echo "<label for='stuff'>Additional Stuff</label>";
		echo "<input type='text' name='stuff' />";
		echo "<label for='link'>Links</label>";
		echo "<input type='text' name='link' />";
		echo "<label for='year'>Year</label>";
		echo "<input type='text' name='year' />";
		echo "<p><input type='submit' name='insertsubmit' value='Submit' class='insertlink'/></p>";
	echo "</form>";
}
if(isset($_REQUEST['editaction']))
{

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
}
if(isset($_REQUEST['edit_submit']))
{
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
}

if (isset($_REQUEST['insertsubmit'])) 
{
    $media_title = $_POST["title"];
	$media_description = $_POST["description"];
    $media_type = $_POST["media_type"];
	$media_rating = $_POST["rating_id"];
	$media_stuff = $_POST["stuff"];
	$media_link = $_POST["link"];
	$media_year = $_POST["year"];

	if ($media_type==2)
	{
		$key='4fj73mhn4gm92vff53wnsygr';
		$title=$media_title;
		$link = "http://api.rottentomatoes.com/api/public/v1.0/movies.json?q=".$title."&page_limit=20&apikey=".$key;

		$file = file_get_contents($link);
		$jsonDecode = json_decode($file,True);
		$movie_array = $jsonDecode['movies'][0];

		$tomato_id=$movie_array['id'];
		$movie_title=$movie_array['title'];
		$movie_year=$movie_array['year'];
		$movie_genre=$movie_array['genres'];
		$movie_poster = $movie_array['posters']['thumbnail'];
		$movie_rating = $movie_array['mpaa_rating'];
		$movie_synopsis = $movie_array['synopsis'];
		$movie_link=str_replace(" ","_","http://www.rottentomatoes.com/m/$media_title/");

		If ($tomato_id)
		{
			$query = "INSERT into items VALUES(NULL, '$movie_title', '$movie_genre', '$media_type', '$movie_rating', '$media_stuff', '$movie_link', '$movie_year', '$_SESSION(user_id)')";
			queryfunc($query);
		}
		else
		{
			echo "No Movie named ".$title." on file";
		}
	}
	else if($media_type!=2)
	{
		$query = "INSERT into items VALUES(NULL, '$media_title', '$media_description', '$media_type','$media_rating','$media_stuff','$media_link','$media_year','$_SESSION(user_id)')";
		if ($media_title!="")
		{
			queryfunc($query);
		}
	}
}

if(isset($_REQUEST['deleteaction']))
{
	$deletequery="delete from `items` where `item_id`='".$_REQUEST[item_id]."'";
	queryfunc($deletequery);
}


if(isset($_REQUEST['editsubmit']))
{
	$editquery = "UPDATE `items` SET `title`='".$_REQUEST[title]."', `description`='".$_REQUEST[description]."', `media_type`='".$_REQUEST[media_type]."', `rating_id`='".$_REQUEST[rating_id]."',`stuff`='".$_REQUEST[stuff]."',`link`='".$_REQUEST[link]."', `year`='".$_REQUEST[year]."' WHERE `item_id`='".$_REQUEST[item_id]."'";
	echo $editquery;
	queryfunc($editquery);
}

echo "<h2>Music</h2>";
echo "<table>";
echo "<tr>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">MID</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Title</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Description</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Media Type</a></td>";
echo "<p>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Rating</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Stuff</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Link</a></td>";
echo "<td><a style=\"font-size:15px;font-family:ariel;\">Year</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">UID</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">Delete</a></td>";
echo "<td style=\"font-size:15px;font-family:ariel;\">Edit</a></td>";
echo "</tr>";

$query="select * from items";
$results=queryfunc($query);

while ($row=mysqli_fetch_array($results))//mysqli_fetch_assoc while i can fetch a row out of the results with using column name in [] below//if fetch array you can use index numbers in [] below
{
	echo "<form method='POST' action='".$_SERVER[item_id]."'>";
	echo "<tr>";
	echo "<td>$row[item_id]</td>";
	echo "<td class='$row[title]'>$row[title]</td>";
	echo "<td class='$row[description]'>$row[description]</td>";
	echo "<td class='$row[media_type]'>$row[media_type]</td>";
	echo "<td class='$row[rating_id]'>$row[rating_id]</td>";
	echo "<td class='$row[stuff]'>$row[stuff]</td>";
	echo "<td class='$row[link]'>$row[link]</td>";
	echo "<td class='$row[year]'>$row[year]</td>";
	echo "<td class='$row[user_id]'>$row[user_id]</td>";
	echo "<td> <a class='deleteLink' type='hidden' style=\"color:blue;font-size:15px;font-family:ariel;\" href=\"./addmedia.php?deleteaction=delete&item_id=$row[item_id]\">Delete</a></td>";
	echo "<td> <a class='editLink' type='hidden' style=\"color:blue;font-size:15px;font-family:ariel;\" href=\"./addmedia.php?editaction=edit&item_id=$row[item_id]\">Edit</a></td>";
	//echo "<td> <input type='submit' class='deleteLink' name='deleteaction' value='Delete'></td>";
	//echo "<td> <a class='editLink' style=\"color:blue;font-size:15px;font-family:ariel;\">Edit</a></td>";
	echo "</tr>";
	echo "</form>";
}

include_once "footer.php";

/*

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
*/
?>