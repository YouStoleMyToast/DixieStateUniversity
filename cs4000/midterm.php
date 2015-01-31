<!DOCTYPE html>

<html>
<form method="POST" action="http://vt4000.cs.dixie.edu/midterm/sample.php">
<select name=ProductName>
	<option>Tucker</option>
	<option>Studebaker</option>
	<option>DeSoto</option>
	<option>Edsel</option>
	<option>Packard</option>
	<option>Plymouth Valient</option>
	<option>Dodge Dart</option>
	<option>Ford Falcon</option>
</select>

<label for="ProductLine">Product Line</label>
<input type="text" name="ProductLine">

<label for="ProductDescription">Product Description</label>
<input type="text" name="ProductDescription">

<label for="image_link">Image Link</label>
<input type="text" name="image_link">

<input type="submit" name="submiter" value="Submit"/>
</form>


<?php
if (isset($_POST)) 
{
	$ProductCode=time();
	$ProductName=$_POST['ProductName'];
	$ProductLine=$_POST['ProductLine'];
	$ProductDescription=$_POST['ProductDescription'];
	$image_link=$_POST['image_link'];

	$query = "insert into products values('.$ProductCode.','.$ProductName.','.$ProductLine.','.$ProductDescription.','.$image_link')";
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
	$result = mysqli_query($connect, $query) or die("can't do query" . $query . mysqli_error($connect));
}

?>



</html>